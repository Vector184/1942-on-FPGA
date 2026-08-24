module sprite_background_tb;

logic vga_clk, blank;
logic reset;
logic [9:0] DrawX, DrawY;
logic [3:0] red, green, blue;
logic [31:0] game_regs [0:7];

sprite_background_example dut (
    .vga_clk(vga_clk),
    .reset(reset),
    .DrawX(DrawX),
    .DrawY(DrawY),
    .game_regs(game_regs),
    .blank(blank),
    .red(red),
    .green(green),
    .blue(blue)
);

always #20 vga_clk = ~vga_clk;

integer file;

initial begin
    vga_clk = 0;
    reset = 1;
    blank = 1;
    game_regs[0] = 32'd0;
    DrawX = 0;
    DrawY = 0;

    repeat (2) @(posedge vga_clk);
    reset = 0;

    file = $fopen("output.ppm", "w");
    $fwrite(file, "P3\n256 240\n255\n");

for (int y = 0; y < 240; y++) begin
    for (int x = 0; x < 256; x++) begin
        DrawX = x;
        DrawY = y;
        @(negedge vga_clk); // ROM reads address
        @(posedge vga_clk); // ROM outputs data
        @(posedge vga_clk); // color_mapper registers it
        $fwrite(file, "%0d %0d %0d\n",
            {red,   red},
            {green, green},
            {blue,  blue});
    end
end

    $fclose(file);
    $display("Done - open output.ppm");
    $finish;
end

endmodule
