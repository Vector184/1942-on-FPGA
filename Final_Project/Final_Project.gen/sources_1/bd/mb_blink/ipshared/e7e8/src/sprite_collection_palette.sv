module sprite_collection_palette (
	input logic [4:0] index,
	input logic [1:0] palette_id,
	output logic [3:0] red, green, blue
);

localparam [0:31][11:0] palette = {
	{4'hF, 4'h5, 4'hF},
	{4'hF, 4'h5, 4'hF},
	{4'hF, 4'hF, 4'hF},
	{4'hD, 4'h2, 4'h0},
	{4'hB, 4'hB, 4'hB},
	{4'h7, 4'hC, 4'h1},
	{4'h0, 4'h9, 4'h0},
	{4'hF, 4'h7, 4'h6},
	{4'h7, 4'h7, 4'h7},
	{4'h2, 4'h8, 4'h2},
	{4'hD, 4'h2, 4'h2},
	{4'hF, 4'h5, 4'hF},
	{4'hF, 4'h5, 4'hF},
	{4'hF, 4'h5, 4'hF},
	{4'hF, 4'h5, 4'hF},
	{4'hF, 4'h5, 4'hF},
	{4'hF, 4'h5, 4'hF},
	{4'hF, 4'h5, 4'hF},
	{4'hF, 4'h5, 4'hF},
	{4'hF, 4'h5, 4'hF},
	{4'hF, 4'h5, 4'hF},
	{4'hF, 4'h5, 4'hF},
	{4'hF, 4'h5, 4'hF},
	{4'hF, 4'h5, 4'hF},
	{4'hF, 4'h5, 4'hF},
	{4'hF, 4'h5, 4'hF},
	{4'hF, 4'h5, 4'hF},
	{4'hF, 4'h5, 4'hF},
	{4'hF, 4'hB, 4'h3},
	{4'hF, 4'h5, 4'hF},
	{4'hF, 4'h5, 4'hF},
	{4'hF, 4'h5, 4'hF}
};

always_comb begin
	{red, green, blue} = palette[index];

	if (palette_id == 2'd1) begin
		if (palette[index] == 12'hFB3) begin
			{red, green, blue} = 12'h7C1;
		end else if (palette[index] == 12'hD20) begin
			{red, green, blue} = 12'h090;
		end else if (palette[index] == 12'hFFF) begin
			{red, green, blue} = 12'hD20;
		end
	end
end

endmodule
