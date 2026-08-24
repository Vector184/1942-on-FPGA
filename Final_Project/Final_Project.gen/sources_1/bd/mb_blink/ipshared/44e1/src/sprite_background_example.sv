module sprite_background_example (
	input logic vga_clk,
	input logic reset,
	input logic [9:0] DrawX, DrawY,
	input logic [31:0] game_regs [0:7],
	input logic blank,
	output logic [3:0] red, green, blue
);

logic [18:0] rom_address;
logic [3:0] rom_q;
logic [18:0] overlay_rom_address;
logic [3:0] overlay_rom_q;

logic [3:0] palette_red, palette_green, palette_blue;
logic [3:0] overlay_red, overlay_green, overlay_blue;

logic negedge_vga_clk;

// read from ROM on negedge, set pixel on posedge
assign negedge_vga_clk = ~vga_clk;


localparam CARRIER_BASE_X = 0;
localparam CARRIER_BASE_Y = 964;
localparam CARRIER_W = 96;
localparam CARRIER_H = 224;


 localparam ISLAND_BASE_X = 96;
 localparam ISLAND_BASE_Y = 964;
 localparam ISLAND_W = 160;
 localparam ISLAND_H = 112;


localparam OCEAN_BASE_X = 96;
localparam OCEAN_BASE_Y = 1076;
localparam OCEAN_W = 32;
localparam OCEAN_H = 16;
localparam START_SCREEN_BASE_X = 0;
localparam START_SCREEN_BASE_Y = 0;
localparam START_SCREEN_W = 256;
localparam START_SCREEN_H = 240;
localparam INTRO_OVERLAY_BASE_X = 0;
localparam INTRO_OVERLAY_BASE_Y = 480;
localparam INTRO_OVERLAY_W = 256;
localparam INTRO_OVERLAY_H = 240;
localparam STATS_OVERLAY_BASE_X = 0;
localparam STATS_OVERLAY_BASE_Y = 724;
localparam STATS_OVERLAY_W = 256;
localparam STATS_OVERLAY_H = 240;

localparam CARRIER_SCREEN_X = 80;
localparam CARRIER_LEVEL_Y = 0; 

localparam ISLAND_SCREEN_X  = 96;
localparam ISLAND_LEVEL_Y  = 512;
localparam ISLAND2_LEVEL_Y = 992;

localparam LEVEL_H = 1872; // currently changed from 1904 to 1872
localparam SCROLL_WRAP_Y = LEVEL_H + CARRIER_H;
localparam START_SCROLL_Y = 12'd0;


logic [11:0] scroll_y = START_SCROLL_Y;
logic [5:0] frame_count = 6'd0;
logic frame_pulse;
assign frame_pulse = (DrawX == 255) && (DrawY == 239);

always_ff @(posedge vga_clk or posedge reset) begin
    if (reset) begin
        scroll_y <= START_SCROLL_Y;
        frame_count <= 6'd0;
    end else if (game_regs[0][1] || game_regs[0][2]) begin
        scroll_y <= START_SCROLL_Y;
        frame_count <= 6'd0;
    end else if (frame_pulse) begin
        if (frame_count >= 16) begin 
            frame_count <= 0;
            if (scroll_y >= SCROLL_WRAP_Y - 1) begin
                scroll_y <= 0;
            end else begin
                scroll_y <= scroll_y + 1;
            end
        end else begin
            frame_count <= frame_count + 1;
        end
    end
end

logic [11:0] world_y;
logic carrier_on, carrier_on_reg;
logic [9:0] carrier_rel_x, carrier_rel_y;

always_comb begin
    if (DrawY >= scroll_y) begin
        world_y = DrawY - scroll_y;
    end else begin
        world_y = DrawY + SCROLL_WRAP_Y - scroll_y;
    end
end

assign carrier_on = (DrawX >= CARRIER_SCREEN_X) && (DrawX < CARRIER_SCREEN_X + CARRIER_W) && (world_y >= CARRIER_LEVEL_Y) && (world_y < CARRIER_LEVEL_Y + CARRIER_H);

always_comb begin
    if (carrier_on) begin
        carrier_rel_x = DrawX - CARRIER_SCREEN_X;
        carrier_rel_y = world_y - CARRIER_LEVEL_Y;
    end else begin
        carrier_rel_x = 10'd0;
        carrier_rel_y = 10'd0;
    end
end

logic island_on, island2_on, island_on_reg;
logic [9:0] island_rel_x, island_rel_y;

assign island_on = (DrawX >= ISLAND_SCREEN_X) && (DrawX < ISLAND_SCREEN_X + ISLAND_W) && (world_y >= ISLAND_LEVEL_Y) && (world_y < ISLAND_LEVEL_Y + ISLAND_H);
assign island2_on = (DrawX >= ISLAND_SCREEN_X) && (DrawX < ISLAND_SCREEN_X + ISLAND_W) && (world_y >= ISLAND2_LEVEL_Y) && (world_y < ISLAND2_LEVEL_Y + ISLAND_H);

always_comb begin
    if (island_on) begin
        island_rel_x = DrawX - ISLAND_SCREEN_X;
        island_rel_y = world_y - ISLAND_LEVEL_Y;
    end else if (island2_on) begin
        island_rel_x = DrawX - ISLAND_SCREEN_X;
        island_rel_y = world_y - ISLAND2_LEVEL_Y;
    end else begin
        island_rel_x = 10'd0;
        island_rel_y = 10'd0;
    end
end


logic [4:0] tile_x;
logic [3:0] tile_y;

assign tile_x = DrawX[4:0];
//assign tile_x = 0;
assign tile_y = (DrawY + OCEAN_H - (scroll_y % OCEAN_H)) % OCEAN_H;


// address into the rom = (x*xDim)/640 + ((y*yDim)/480) * xDim
// this will stretch out the sprite across the entire screen
//assign rom_address = ((DrawX * 256) / 640) + (((DrawY * 1188) / 480) * 256);

always_comb begin
    if (carrier_on)
        rom_address = (CARRIER_BASE_Y + carrier_rel_y) * 256 + (CARRIER_BASE_X + carrier_rel_x);
    else if (island_on || island2_on)
        rom_address = (ISLAND_BASE_Y + island_rel_y) * 256 + (ISLAND_BASE_X + island_rel_x);
    else
        rom_address = (OCEAN_BASE_Y + tile_y) * 256 + (OCEAN_BASE_X + tile_x);
end

always_comb begin
    if (game_regs[0][1] && DrawX < START_SCREEN_W && DrawY < START_SCREEN_H)
        overlay_rom_address = (START_SCREEN_BASE_Y + DrawY) * 256 + (START_SCREEN_BASE_X + DrawX);
    else if (game_regs[0][2] && DrawX < STATS_OVERLAY_W && DrawY < STATS_OVERLAY_H)
        overlay_rom_address = (STATS_OVERLAY_BASE_Y + DrawY) * 256 + (STATS_OVERLAY_BASE_X + DrawX);
    else if (game_regs[0][0] && DrawX < INTRO_OVERLAY_W && DrawY < INTRO_OVERLAY_H)
        overlay_rom_address = (INTRO_OVERLAY_BASE_Y + DrawY) * 256 + (INTRO_OVERLAY_BASE_X + DrawX);
    else
        overlay_rom_address = 19'd0;
end

always_ff @(posedge vga_clk) begin
    carrier_on_reg <= carrier_on;
    island_on_reg  <= island_on || island2_on;
end


always_ff @ (posedge vga_clk) begin
	red <= 4'h0;
	green <= 4'h0;
	blue <= 4'h0;

	if (blank) begin
		if (game_regs[0][1]) begin
			red <= overlay_red;
			green <= overlay_green;
			blue <= overlay_blue;
		end else if (game_regs[0][2] && ({overlay_red, overlay_green, overlay_blue} != 12'hF5F)) begin
			red <= overlay_red;
			green <= overlay_green;
			blue <= overlay_blue;
		end else if (game_regs[0][0] && ({overlay_red, overlay_green, overlay_blue} != 12'hF5F)) begin
			red <= overlay_red;
			green <= overlay_green;
			blue <= overlay_blue;
		end else begin
			red <= palette_red;
			green <= palette_green;
			blue <= palette_blue;
		end
	end
end



sprite_background_rom sprite_background_rom (
	.clka   (negedge_vga_clk),
	.addra (rom_address),
	.douta (rom_q),
	.clkb   (negedge_vga_clk),
	.addrb (overlay_rom_address),
	.doutb (overlay_rom_q)
);

sprite_background_palette sprite_background_palette (
	.index (rom_q),
	.red   (palette_red),
	.green (palette_green),
	.blue  (palette_blue)
);

sprite_background_palette intro_overlay_palette (
	.index (overlay_rom_q),
	.red   (overlay_red),
	.green (overlay_green),
	.blue  (overlay_blue)
);

endmodule
