module bkg_example (
	input logic vga_clk,
	input logic [9:0] DrawX, DrawY,
	input logic blank, vsync,
	output logic [3:0] red, green, blue
);

logic [14:0] rom_address;
logic [2:0] rom_q;

logic [3:0] palette_red, palette_green, palette_blue;

logic negedge_vga_clk;

// read from ROM on negedge, set pixel on posedge
assign negedge_vga_clk = ~vga_clk;

// address into the rom = (x*xDim)/640 + ((y*yDim)/480) * xDim
// this will stretch out the sprite across the entire screen



//assign rom_address = ((DrawX * 256) / 640) + (((DrawY * 128) / 480) * 256);

 logic frame_pulse;
assign frame_pulse = (DrawX == 255) && (DrawY == 239);
logic [9:0] scroll_y;  // current scroll offset
logic [5:0] frame_count;
// In an always_ff block clocked by a slow enable (once per frame)
always_ff @(posedge vga_clk) begin
    if (frame_pulse) begin
        if (frame_count >= 10) begin 
            frame_count <= 0;
            if (scroll_y >= 127)
                scroll_y <= 0;
            else
                scroll_y <= scroll_y + 1;
        end else begin
            frame_count <= frame_count + 1;
        end
    end
end

// Modify address to use offset Y
logic [9:0] scrolled_y;
//assign scrolled_y = (DrawY - scroll_y + 480) % 480;
assign scrolled_y  = (DrawY + 128 - scroll_y) % 128;
//assign rom_address = ((DrawX * 256) / 640) + (((scrolled_y * 128) / 480) * 256);
assign rom_address = DrawX + (scrolled_y * 256);






always_ff @ (posedge vga_clk) begin
	red <= 4'h0;
	green <= 4'h0;
	blue <= 4'h0;

	if (blank) begin
		red <= palette_red;
		green <= palette_green;
		blue <= palette_blue;
	end
end

bkg_rom bkg_rom (
	.clka   (negedge_vga_clk),
	.addra (rom_address),
	.douta       (rom_q)
);

bkg_palette bkg_palette (
	.index (rom_q),
	.red   (palette_red),
	.green (palette_green),
	.blue  (palette_blue)
);

endmodule
