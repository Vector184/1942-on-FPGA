module sprite_background_rom (
	input logic clka,
	input logic [18:0] addra,
	output logic [3:0] douta,
	input logic clkb,
	input logic [18:0] addrb,
	output logic [3:0] doutb
);

background_bram bkg_bram(
    .clka(clka),
    .addra(addra),
    .douta(douta),
    .ena(1),
    .clkb(clkb),
    .addrb(addrb),
    .doutb(doutb),
    .enb(1)
);

endmodule
