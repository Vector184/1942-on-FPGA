module sprite_collection_rom (
	input logic clock,
	input logic [14:0] address,
	output logic [4:0] q
);

logic [4:0] memory [0:30719] /* synthesis ram_init_file = "./sprite_collection/sprite_collection.COE" */;

always_ff @ (posedge clock) begin
	q <= memory[address];
end

endmodule
