// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2022.2 (win64) Build 3671981 Fri Oct 14 05:00:03 MDT 2022
// Date        : Tue May  5 22:58:53 2026
// Host        : ECEB-3022-15 running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub
//               c:/Users/kakkar3/Desktop/Final_Project/ip_repo/hdmi_text_controller_1_0/src/background_bram/background_bram_stub.v
// Design      : background_bram
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7s50csga324-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* x_core_info = "blk_mem_gen_v8_4_5,Vivado 2022.2" *)
module background_bram(clka, ena, addra, douta, clkb, enb, addrb, doutb)
/* synthesis syn_black_box black_box_pad_pin="clka,ena,addra[18:0],douta[3:0],clkb,enb,addrb[18:0],doutb[3:0]" */;
  input clka;
  input ena;
  input [18:0]addra;
  output [3:0]douta;
  input clkb;
  input enb;
  input [18:0]addrb;
  output [3:0]doutb;
endmodule
