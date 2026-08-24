module sprite_collection_rom (
	input logic clka,
	input logic [14:0] addra,
	output logic [4:0] douta,
	input logic clkb,
	input logic [14:0] addrb,
	output logic [4:0] doutb
);

sprite_bram sprite_rom(
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
