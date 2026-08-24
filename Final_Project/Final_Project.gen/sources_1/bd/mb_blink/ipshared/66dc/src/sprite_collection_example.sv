module sprite_collection_example (
	input logic vga_clk,
	input logic [9:0] DrawX, DrawY,
	input logic [31:0] oam_regs [0:63],
	input logic blank,
	output logic [3:0] red, green, blue,
	output logic sprite_on_reg
);

// OAM format per register:
// [7:0]   Y coordinate
// [15:8]  Tile index
// [23:16] Attributes
// [31:24] X coordinate


localparam int OAM_SPRITE_COUNT = 64;

function automatic signed [10:0] sprite_left(input logic [7:0] x, input logic [7:0] attr);
	if (attr[5] && attr[1:0] == 2'd1) begin
		sprite_left = {3'b111, x};
	end else begin
		sprite_left = {3'b000, x};
	end
endfunction

logic [14:0] rom_address;
logic [4:0] rom_q;
logic [14:0] under_rom_address;
logic [4:0] under_rom_q;

logic [31:0] selected_oam;
logic [31:0] under_oam;
logic [26:0] selected_sprite_data;
logic [26:0] under_sprite_data;
logic selected_sprite_on;
logic under_sprite_on;
logic [7:0] sprite_y, attributes, sprite_x;
logic [7:0] under_sprite_y, under_attributes, under_sprite_x;
logic [26:0] sprite_data;
logic [26:0] under_sprite_data_active;
logic [5:0] sprite_w, sprite_h;
logic [5:0] under_sprite_w, under_sprite_h;
logic [7:0] sheet_x;
logic [6:0] sheet_y;
logic [7:0] under_sheet_x;
logic [6:0] under_sheet_y;
logic [9:0] rel_x, rel_y;
logic [9:0] rom_rel_x, rom_rel_y;
logic [9:0] under_rel_x, under_rel_y;
logic [9:0] under_rom_rel_x, under_rom_rel_y;
logic signed [10:0] draw_x;
logic signed [10:0] selected_sprite_left, under_sprite_left;

logic [3:0] palette_red, palette_green, palette_blue;
logic [3:0] under_palette_red, under_palette_green, under_palette_blue;
logic top_pixel_visible, under_pixel_visible;
logic sprite_on_q, under_sprite_on_q;
logic sprite_on;
logic negedge_vga_clk;

logic [7:0] oam_y [0:OAM_SPRITE_COUNT-1];
logic [7:0] oam_tile [0:OAM_SPRITE_COUNT-1];
logic [7:0] oam_x [0:OAM_SPRITE_COUNT-1];
logic signed [10:0] oam_left [0:OAM_SPRITE_COUNT-1];
logic signed [10:0] oam_right [0:OAM_SPRITE_COUNT-1];
logic [26:0] oam_sprite_data [0:OAM_SPRITE_COUNT-1];
logic [5:0] oam_w [0:OAM_SPRITE_COUNT-1];
logic [5:0] oam_h [0:OAM_SPRITE_COUNT-1];

genvar oam_i;
generate
	for (oam_i = 0; oam_i < OAM_SPRITE_COUNT; oam_i++) begin : OAM_DECODE
		assign oam_y[oam_i] = oam_regs[oam_i][7:0];
		assign oam_tile[oam_i] = oam_regs[oam_i][15:8];
		assign oam_x[oam_i] = oam_regs[oam_i][31:24];
		assign oam_left[oam_i] = sprite_left(oam_x[oam_i], oam_regs[oam_i][23:16]);
		assign oam_w[oam_i] = oam_sprite_data[oam_i][26:21];
		assign oam_h[oam_i] = oam_sprite_data[oam_i][20:15];
		assign oam_right[oam_i] = oam_left[oam_i] + $signed({5'b0, oam_w[oam_i]});

		lookup_table sprite_lookup (
			.addr(oam_tile[oam_i]),
			.data(oam_sprite_data[oam_i])
		);
	end
endgenerate

always_comb begin
	selected_oam = 32'd0;
	under_oam = 32'd0;
	selected_sprite_data = 27'd0;
	under_sprite_data = 27'd0;
	selected_sprite_on = 1'b0;
	under_sprite_on = 1'b0;

	for (int i = 0; i < OAM_SPRITE_COUNT; i++) begin
		if ((oam_regs[i] != 32'd0) &&
			(oam_w[i] != 6'd0) &&
			(oam_h[i] != 6'd0) &&
			(draw_x >= oam_left[i]) &&
			(draw_x < oam_right[i]) &&
			(DrawY >= {2'b0, oam_y[i]}) &&
			(DrawY < ({2'b0, oam_y[i]} + {4'b0, oam_h[i]}))) begin

			under_oam = selected_oam;
			under_sprite_data = selected_sprite_data;
			under_sprite_on = selected_sprite_on;
			selected_oam = oam_regs[i];
			selected_sprite_data = oam_sprite_data[i];
			selected_sprite_on = 1'b1;
		end
	end
end

assign sprite_y = selected_oam[7:0];
assign attributes = selected_oam[23:16];
assign sprite_x = selected_oam[31:24];
assign sprite_data = selected_sprite_data;
assign selected_sprite_left = sprite_left(sprite_x, attributes);
assign under_sprite_y = under_oam[7:0];
assign under_attributes = under_oam[23:16];
assign under_sprite_x = under_oam[31:24];
assign under_sprite_data_active = under_sprite_data;
assign under_sprite_left = sprite_left(under_sprite_x, under_attributes);

assign sprite_w = sprite_data[26:21];
assign sprite_h = sprite_data[20:15];
assign sheet_x = sprite_data[14:7];
assign sheet_y = sprite_data[6:0];
assign under_sprite_w = under_sprite_data_active[26:21];
assign under_sprite_h = under_sprite_data_active[20:15];
assign under_sheet_x = under_sprite_data_active[14:7];
assign under_sheet_y = under_sprite_data_active[6:0];

assign draw_x = {1'b0, DrawX};
assign rel_x = draw_x - selected_sprite_left;
assign rel_y = DrawY - {2'b0, sprite_y};
assign under_rel_x = draw_x - under_sprite_left;
assign under_rel_y = DrawY - {2'b0, under_sprite_y};

assign sprite_on = selected_sprite_on;

always_comb begin
	if (attributes[6]) begin
		rom_rel_x = {4'b0, sprite_w} - 10'd1 - rel_x;
	end else begin
		rom_rel_x = rel_x;
	end

	if (attributes[7]) begin
		rom_rel_y = {4'b0, sprite_h} - 10'd1 - rel_y;
	end else begin
		rom_rel_y = rel_y;
	end

	if (under_attributes[6]) begin
		under_rom_rel_x = {4'b0, under_sprite_w} - 10'd1 - under_rel_x;
	end else begin
		under_rom_rel_x = under_rel_x;
	end

	if (under_attributes[7]) begin
		under_rom_rel_y = {4'b0, under_sprite_h} - 10'd1 - under_rel_y;
	end else begin
		under_rom_rel_y = under_rel_y;
	end
end

// read from ROM on negedge, set pixel on posedge
assign negedge_vga_clk = ~vga_clk;

always_ff @ (posedge negedge_vga_clk) begin
	sprite_on_q <= sprite_on;
	under_sprite_on_q <= under_sprite_on;
end

// address into the sprite sheet ROM
always_comb begin
	if (sprite_on) begin
		rom_address = ((sheet_y + rom_rel_y) * 256 + (sheet_x + rom_rel_x));
	end else begin
		rom_address = 15'd0;
	end
end

always_comb begin
	if (under_sprite_on) begin
		under_rom_address = ((under_sheet_y + under_rom_rel_y) * 256 + (under_sheet_x + under_rom_rel_x));
	end else begin
		under_rom_address = 15'd0;
	end
end
assign top_pixel_visible = sprite_on_q && ({palette_red, palette_green, palette_blue} != 12'hF5F);
assign under_pixel_visible = under_sprite_on_q && ({under_palette_red, under_palette_green, under_palette_blue} != 12'hF5F);

always_ff @ (posedge vga_clk) begin
	red <= 4'h0;
	green <= 4'h0;
	blue <= 4'h0;
	sprite_on_reg <= top_pixel_visible || under_pixel_visible;

	if (blank) begin
		if (top_pixel_visible) begin
			red <= palette_red;
			green <= palette_green;
			blue <= palette_blue;
		end else if (under_pixel_visible) begin
			red <= under_palette_red;
			green <= under_palette_green;
			blue <= under_palette_blue;
		end else begin
			red <= 4'hF;
			green <= 4'h5;
			blue <= 4'hF;
		end
	end
end

sprite_collection_rom sprite_collection_rom (
	.clka   (negedge_vga_clk),
	.addra (rom_address),
	.douta  (rom_q),
	.clkb   (negedge_vga_clk),
	.addrb (under_rom_address),
	.doutb  (under_rom_q)
);

sprite_collection_palette sprite_collection_palette (
	.index (rom_q),
	.palette_id (attributes[1:0]),
	.red   (palette_red),
	.green (palette_green),
	.blue  (palette_blue)
);

sprite_collection_palette under_sprite_collection_palette (
	.index (under_rom_q),
	.palette_id (under_attributes[1:0]),
	.red   (under_palette_red),
	.green (under_palette_green),
	.blue  (under_palette_blue)
);

endmodule
