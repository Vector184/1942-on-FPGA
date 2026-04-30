module sprite_background_rom (
	input logic clock,
	input logic [17:0] address,
	output logic [3:0] q
);

logic [3:0] memory [0:250623] /* synthesis ram_init_file = "./sprite_background/sprite_background.COE" */;

always_ff @ (posedge clock) begin
	q <= memory[address];
end

endmodule
