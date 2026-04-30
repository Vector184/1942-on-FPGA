module sprite_collection_rom (
	input logic clock,
	input logic [16:0] address,
	output logic [4:0] q
);

logic [4:0] memory [0:87807] /* synthesis ram_init_file = "./sprite_collection/sprite_collection.COE" */;

always_ff @ (posedge clock) begin
	q <= memory[address];
end

endmodule
