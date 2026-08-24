module bkg_rom (
	input logic clka,
	input logic [14:0] addra,
	output logic [2:0] douta
);

blk_mem_gen_0 bkg_bram(
    .addra(addra),
    .clka(clka),
    .douta(douta),
    .ena(1)
);

endmodule
