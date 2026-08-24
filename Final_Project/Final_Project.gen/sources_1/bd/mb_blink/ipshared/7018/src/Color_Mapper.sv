//-------------------------------------------------------------------------
//    Color_Mapper.sv                                                    --
//    Stephen Kempf                                                      --
//    3-1-06                                                             --
//                                                                       --
//    Modified by David Kesler  07-16-2008                               --
//    Translated by Joe Meng    07-07-2013                               --
//    Modified by Zuofu Cheng   08-19-2023                               --
//                                                                       --
//    Fall 2023 Distribution                                             --
//                                                                       --
//    For use with ECE 385 USB + HDMI                                    --
//    University of Illinois ECE Department                              --
//-------------------------------------------------------------------------


module  color_mapper ( input  logic [9:0] DrawX, DrawY,
                        input logic vga_clk, blank, vsync, reset,
                        input logic [31:0] oam_regs [0:63],
                        input logic [31:0] game_regs [0:7],
                       output logic [3:0]  Red, Green, Blue );
    

	 
 /* Old Ball: Generated square box by checking if the current pixel is within a square of length
    2*BallS, centered at (BallX, BallY).  Note that this requires unsigned comparisons.
	 
    if ((DrawX >= BallX - Ball_size) &&
       (DrawX <= BallX + Ball_size) &&
       (DrawY >= BallY - Ball_size) &&
       (DrawY <= BallY + Ball_size))
       )

     New Ball: Generates (pixelated) circle by using the standard circle formula.  Note that while 
     this single line is quite powerful descriptively, it causes the synthesis tool to use up three
     of the 120 available multipliers on the chip!  Since the multiplicants are required to be signed,
	  we have to first cast them from logic to int (signed by default) before they are multiplied). */
	  
  
    logic [3:0] sprite_R, sprite_G, sprite_B, bkg_R, bkg_G, bkg_B;
    
    logic sprite_on;
  
  
     logic [9:0] GameX, GameY;
     logic in_frame;  
     assign in_frame = (DrawX >= 64) && (DrawX < 576);

    always_comb begin
    if (in_frame)
        GameX = (DrawX - 64) >> 1;
    else
        GameX = 10'd0;
    end
    
     assign GameY = DrawY >> 1;         
  
    sprite_collection_example sprite(
        .vga_clk(vga_clk),
        .DrawX(GameX),
        .DrawY(GameY),
        .oam_regs(oam_regs),
        .blank(blank),
        .red(sprite_R),
        .green(sprite_G),
        .blue(sprite_B),
        .sprite_on_reg(sprite_on)
    );
  
//  bkg_example background(
//        .vga_clk(vga_clk),
//        .DrawX(GameX),
//        .DrawY(GameY),
//        .blank(blank),
//        .red(bkg_R),
//        .green(bkg_G),
//        .blue(bkg_B),
//        .vsync(vsync)
//    );
    
  sprite_background_example background(
        .vga_clk(vga_clk),
        .reset(reset),
        .DrawX(GameX),
        .DrawY(GameY),
        .game_regs(game_regs),
        .blank(blank),
        .red(bkg_R),
        .green(bkg_G),
        .blue(bkg_B)
    );



    always_comb
    begin:RGB_Display
       if (!in_frame) begin
           Red = 4'b0;
           Green = 4'b0;
           Blue = 4'b0;
       end
       else if ((sprite_on == 1'b1)&& ({sprite_R, sprite_G, sprite_B} != 12'hF5F)) begin
            Red = sprite_R;
            Green = sprite_G;
            Blue = sprite_B;
        end       
        else begin 
            Red = bkg_R; 
            Green = bkg_G;
            Blue = bkg_B;
        end      
    end 
    
endmodule
