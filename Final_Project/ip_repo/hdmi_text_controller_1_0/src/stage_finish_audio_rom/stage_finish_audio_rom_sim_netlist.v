// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2022.2 (win64) Build 3671981 Fri Oct 14 05:00:03 MDT 2022
// Date        : Thu May  7 11:36:30 2026
// Host        : ECEB-3022-15 running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode funcsim
//               c:/Users/kakkar3/Desktop/Final_Project/ip_repo/hdmi_text_controller_1_0/src/stage_finish_audio_rom/stage_finish_audio_rom_sim_netlist.v
// Design      : stage_finish_audio_rom
// Purpose     : This verilog netlist is a functional simulation representation of the design and should not be modified
//               or synthesized. This netlist cannot be used for SDF annotated simulation.
// Device      : xc7s50csga324-1
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CHECK_LICENSE_TYPE = "stage_finish_audio_rom,blk_mem_gen_v8_4_5,{}" *) (* downgradeipidentifiedwarnings = "yes" *) (* x_core_info = "blk_mem_gen_v8_4_5,Vivado 2022.2" *) 
(* NotValidForBitStream *)
module stage_finish_audio_rom
   (clka,
    ena,
    addra,
    douta);
  (* x_interface_info = "xilinx.com:interface:bram:1.0 BRAM_PORTA CLK" *) (* x_interface_parameter = "XIL_INTERFACENAME BRAM_PORTA, MEM_SIZE 8192, MEM_WIDTH 32, MEM_ECC NONE, MASTER_TYPE OTHER, READ_LATENCY 1" *) input clka;
  (* x_interface_info = "xilinx.com:interface:bram:1.0 BRAM_PORTA EN" *) input ena;
  (* x_interface_info = "xilinx.com:interface:bram:1.0 BRAM_PORTA ADDR" *) input [10:0]addra;
  (* x_interface_info = "xilinx.com:interface:bram:1.0 BRAM_PORTA DOUT" *) output [15:0]douta;

  wire [10:0]addra;
  wire clka;
  wire [15:0]douta;
  wire ena;
  wire NLW_U0_dbiterr_UNCONNECTED;
  wire NLW_U0_rsta_busy_UNCONNECTED;
  wire NLW_U0_rstb_busy_UNCONNECTED;
  wire NLW_U0_s_axi_arready_UNCONNECTED;
  wire NLW_U0_s_axi_awready_UNCONNECTED;
  wire NLW_U0_s_axi_bvalid_UNCONNECTED;
  wire NLW_U0_s_axi_dbiterr_UNCONNECTED;
  wire NLW_U0_s_axi_rlast_UNCONNECTED;
  wire NLW_U0_s_axi_rvalid_UNCONNECTED;
  wire NLW_U0_s_axi_sbiterr_UNCONNECTED;
  wire NLW_U0_s_axi_wready_UNCONNECTED;
  wire NLW_U0_sbiterr_UNCONNECTED;
  wire [15:0]NLW_U0_doutb_UNCONNECTED;
  wire [10:0]NLW_U0_rdaddrecc_UNCONNECTED;
  wire [3:0]NLW_U0_s_axi_bid_UNCONNECTED;
  wire [1:0]NLW_U0_s_axi_bresp_UNCONNECTED;
  wire [10:0]NLW_U0_s_axi_rdaddrecc_UNCONNECTED;
  wire [15:0]NLW_U0_s_axi_rdata_UNCONNECTED;
  wire [3:0]NLW_U0_s_axi_rid_UNCONNECTED;
  wire [1:0]NLW_U0_s_axi_rresp_UNCONNECTED;

  (* C_ADDRA_WIDTH = "11" *) 
  (* C_ADDRB_WIDTH = "11" *) 
  (* C_ALGORITHM = "1" *) 
  (* C_AXI_ID_WIDTH = "4" *) 
  (* C_AXI_SLAVE_TYPE = "0" *) 
  (* C_AXI_TYPE = "1" *) 
  (* C_BYTE_SIZE = "9" *) 
  (* C_COMMON_CLK = "0" *) 
  (* C_COUNT_18K_BRAM = "0" *) 
  (* C_COUNT_36K_BRAM = "1" *) 
  (* C_CTRL_ECC_ALGO = "NONE" *) 
  (* C_DEFAULT_DATA = "0" *) 
  (* C_DISABLE_WARN_BHV_COLL = "0" *) 
  (* C_DISABLE_WARN_BHV_RANGE = "0" *) 
  (* C_ELABORATION_DIR = "./" *) 
  (* C_ENABLE_32BIT_ADDRESS = "0" *) 
  (* C_EN_DEEPSLEEP_PIN = "0" *) 
  (* C_EN_ECC_PIPE = "0" *) 
  (* C_EN_RDADDRA_CHG = "0" *) 
  (* C_EN_RDADDRB_CHG = "0" *) 
  (* C_EN_SAFETY_CKT = "0" *) 
  (* C_EN_SHUTDOWN_PIN = "0" *) 
  (* C_EN_SLEEP_PIN = "0" *) 
  (* C_EST_POWER_SUMMARY = "Estimated Power for IP     :     2.43555 mW" *) 
  (* C_FAMILY = "spartan7" *) 
  (* C_HAS_AXI_ID = "0" *) 
  (* C_HAS_ENA = "1" *) 
  (* C_HAS_ENB = "0" *) 
  (* C_HAS_INJECTERR = "0" *) 
  (* C_HAS_MEM_OUTPUT_REGS_A = "0" *) 
  (* C_HAS_MEM_OUTPUT_REGS_B = "0" *) 
  (* C_HAS_MUX_OUTPUT_REGS_A = "0" *) 
  (* C_HAS_MUX_OUTPUT_REGS_B = "0" *) 
  (* C_HAS_REGCEA = "0" *) 
  (* C_HAS_REGCEB = "0" *) 
  (* C_HAS_RSTA = "0" *) 
  (* C_HAS_RSTB = "0" *) 
  (* C_HAS_SOFTECC_INPUT_REGS_A = "0" *) 
  (* C_HAS_SOFTECC_OUTPUT_REGS_B = "0" *) 
  (* C_INITA_VAL = "0" *) 
  (* C_INITB_VAL = "0" *) 
  (* C_INIT_FILE = "stage_finish_audio_rom.mem" *) 
  (* C_INIT_FILE_NAME = "stage_finish_audio_rom.mif" *) 
  (* C_INTERFACE_TYPE = "0" *) 
  (* C_LOAD_INIT_FILE = "1" *) 
  (* C_MEM_TYPE = "3" *) 
  (* C_MUX_PIPELINE_STAGES = "0" *) 
  (* C_PRIM_TYPE = "1" *) 
  (* C_READ_DEPTH_A = "2048" *) 
  (* C_READ_DEPTH_B = "2048" *) 
  (* C_READ_LATENCY_A = "1" *) 
  (* C_READ_LATENCY_B = "1" *) 
  (* C_READ_WIDTH_A = "16" *) 
  (* C_READ_WIDTH_B = "16" *) 
  (* C_RSTRAM_A = "0" *) 
  (* C_RSTRAM_B = "0" *) 
  (* C_RST_PRIORITY_A = "CE" *) 
  (* C_RST_PRIORITY_B = "CE" *) 
  (* C_SIM_COLLISION_CHECK = "ALL" *) 
  (* C_USE_BRAM_BLOCK = "0" *) 
  (* C_USE_BYTE_WEA = "0" *) 
  (* C_USE_BYTE_WEB = "0" *) 
  (* C_USE_DEFAULT_DATA = "0" *) 
  (* C_USE_ECC = "0" *) 
  (* C_USE_SOFTECC = "0" *) 
  (* C_USE_URAM = "0" *) 
  (* C_WEA_WIDTH = "1" *) 
  (* C_WEB_WIDTH = "1" *) 
  (* C_WRITE_DEPTH_A = "2048" *) 
  (* C_WRITE_DEPTH_B = "2048" *) 
  (* C_WRITE_MODE_A = "WRITE_FIRST" *) 
  (* C_WRITE_MODE_B = "WRITE_FIRST" *) 
  (* C_WRITE_WIDTH_A = "16" *) 
  (* C_WRITE_WIDTH_B = "16" *) 
  (* C_XDEVICEFAMILY = "spartan7" *) 
  (* downgradeipidentifiedwarnings = "yes" *) 
  (* is_du_within_envelope = "true" *) 
  stage_finish_audio_rom_blk_mem_gen_v8_4_5 U0
       (.addra(addra),
        .addrb({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .clka(clka),
        .clkb(1'b0),
        .dbiterr(NLW_U0_dbiterr_UNCONNECTED),
        .deepsleep(1'b0),
        .dina({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .dinb({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .douta(douta),
        .doutb(NLW_U0_doutb_UNCONNECTED[15:0]),
        .eccpipece(1'b0),
        .ena(ena),
        .enb(1'b0),
        .injectdbiterr(1'b0),
        .injectsbiterr(1'b0),
        .rdaddrecc(NLW_U0_rdaddrecc_UNCONNECTED[10:0]),
        .regcea(1'b0),
        .regceb(1'b0),
        .rsta(1'b0),
        .rsta_busy(NLW_U0_rsta_busy_UNCONNECTED),
        .rstb(1'b0),
        .rstb_busy(NLW_U0_rstb_busy_UNCONNECTED),
        .s_aclk(1'b0),
        .s_aresetn(1'b0),
        .s_axi_araddr({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .s_axi_arburst({1'b0,1'b0}),
        .s_axi_arid({1'b0,1'b0,1'b0,1'b0}),
        .s_axi_arlen({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .s_axi_arready(NLW_U0_s_axi_arready_UNCONNECTED),
        .s_axi_arsize({1'b0,1'b0,1'b0}),
        .s_axi_arvalid(1'b0),
        .s_axi_awaddr({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .s_axi_awburst({1'b0,1'b0}),
        .s_axi_awid({1'b0,1'b0,1'b0,1'b0}),
        .s_axi_awlen({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .s_axi_awready(NLW_U0_s_axi_awready_UNCONNECTED),
        .s_axi_awsize({1'b0,1'b0,1'b0}),
        .s_axi_awvalid(1'b0),
        .s_axi_bid(NLW_U0_s_axi_bid_UNCONNECTED[3:0]),
        .s_axi_bready(1'b0),
        .s_axi_bresp(NLW_U0_s_axi_bresp_UNCONNECTED[1:0]),
        .s_axi_bvalid(NLW_U0_s_axi_bvalid_UNCONNECTED),
        .s_axi_dbiterr(NLW_U0_s_axi_dbiterr_UNCONNECTED),
        .s_axi_injectdbiterr(1'b0),
        .s_axi_injectsbiterr(1'b0),
        .s_axi_rdaddrecc(NLW_U0_s_axi_rdaddrecc_UNCONNECTED[10:0]),
        .s_axi_rdata(NLW_U0_s_axi_rdata_UNCONNECTED[15:0]),
        .s_axi_rid(NLW_U0_s_axi_rid_UNCONNECTED[3:0]),
        .s_axi_rlast(NLW_U0_s_axi_rlast_UNCONNECTED),
        .s_axi_rready(1'b0),
        .s_axi_rresp(NLW_U0_s_axi_rresp_UNCONNECTED[1:0]),
        .s_axi_rvalid(NLW_U0_s_axi_rvalid_UNCONNECTED),
        .s_axi_sbiterr(NLW_U0_s_axi_sbiterr_UNCONNECTED),
        .s_axi_wdata({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .s_axi_wlast(1'b0),
        .s_axi_wready(NLW_U0_s_axi_wready_UNCONNECTED),
        .s_axi_wstrb(1'b0),
        .s_axi_wvalid(1'b0),
        .sbiterr(NLW_U0_sbiterr_UNCONNECTED),
        .shutdown(1'b0),
        .sleep(1'b0),
        .wea(1'b0),
        .web(1'b0));
endmodule
`pragma protect begin_protected
`pragma protect version = 1
`pragma protect encrypt_agent = "XILINX"
`pragma protect encrypt_agent_info = "Xilinx Encryption Tool 2022.2"
`pragma protect key_keyowner="Synopsys", key_keyname="SNPS-VCS-RSA-2", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=128)
`pragma protect key_block
VHPlDkoDlWlBfBMvPBmGYmaek3s9hXXhjF28kllYPnaNm3TSnzzpXHWHc8Ye9/2L2yiQfJ1hTWou
Ia/zeQ8h9/dtr6QB5YkyW4wlb/LbMgXb+DGIXPSllNl0IMsRQIcQDbcQm1bO/nlhb+2pjxiuaQrl
DbvxoDwPs7z3LunRxsg=

`pragma protect key_keyowner="Aldec", key_keyname="ALDEC15_001", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
lmIhoX8hXuc7tNV1sXY1K2/gXL7Y7Hq73qQF7+x03UWWTRd3uhGmVQtOMVbhIW+66UkWUHiD26zL
fzqGor8bgSNGpSFyS11k4TwLQT4OfAMGO8C9Qmmh4+VENBnpS9TW+wHzCv8oUwht7xYtYRZvOvYK
F3fMppz2sBkUd1lciw98ZE/UmNkhqBuMfIYF43j45DEJ55PBhOZNg91Ls4v3qBHyBAaYPFFoMry3
d5Fw1PZyFQSEOSSpwgyds2aN0g6oIwl7zm0LJrM9VDAOxBUE50hk+oHr4jj8J8UhHQJnlEHm1Idm
rvxKygNKRvfSpa90NYxZJFYgqnrMYg+19+9aZA==

`pragma protect key_keyowner="Mentor Graphics Corporation", key_keyname="MGC-VELOCE-RSA", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=128)
`pragma protect key_block
VkyCjO2onoeZWEoYQ/4ue7X5mkHyTYVW9xjdoTsGS4GdP/Q64VaCZL/jr6R8DVDXPMnH7tRMrDpo
jpYBnyzSgOkfgqM+96ioC2fDyAaG4gYgGLmrBR6qK3/mxXwAZZX+GJ9R/eWXkc9h8xN+gsSSX6/M
jIQCgeT6q7PB4dWT6KY=

`pragma protect key_keyowner="Mentor Graphics Corporation", key_keyname="MGC-VERIF-SIM-RSA-2", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
Iub91V+TnhVlZCSLu6iKmFjix71y6/l83OPTs8uewWvkE7WcqYxEKi9fonXEkzAtWzuKwEUqnOlN
VBsNJqPUdKcd22q523mrdt89mpdosWD+hvZdO7ELhJniY5u9h49FFkubpN2JiUTcIcKEYxVNlds4
wyvaYUqbPVH5v2ooJwDdimS4GVn9HerCOgPwfshvQDNlMTxLcYju4v8BHMc5Rub9Q/ihvpQU74v2
ouZ9XIwA+C6pBLwvaqS8jE7HXOokgqJilaX/W/t+KEgiFry/txRTMU9WMD7tCN7lcfjCydmS3Lq+
3u6Hsr0S8BwNjcaDpZDnBTygUJd4JSqREnk33w==

`pragma protect key_keyowner="Real Intent", key_keyname="RI-RSA-KEY-1", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
U46EWFmKmpZGaWfyL+dokyQtJtaOYsa7HCW/+fdtw9/yHKTWFpmqKBZngBj5rPkNhtTDDCJkqsYj
tUXg1j4tgIBaCQn9B0q/aG+B3gPLrudp9hLL25mVbsfiTzdekiV2hJMmhuMoavKKPJHC6zyW7kZi
80er82OQy8h+Df/fe6TRjH9xEt3/b80tRKUMbxkLfnnkAyyf1KfOhB6/uyI4mwXuQR+DsAbzybKR
YtXpOiW72tGrXTFlzcwbHamWZefqsilVpBw6V5dh33vYKGx50xwWpj76maAkpQrOpB7zufeldJe4
W1UOEN84AZdRTLkVSxamWo/wp8nP9fiGS/ItRw==

`pragma protect key_keyowner="Xilinx", key_keyname="xilinxt_2021_07", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
qczgIJYpE/SzErzK7eWJBGcDFEzDLm8cKbwJbPXuM6YnJxx44W+E60R3war7K2QGFAkOoCDUtDC7
SghJGF32btaDLzeKm0tQ669sBtQmMIaBrlt7I9QBkNM8zN9GL92qxNC9o3UVWMOYy5BmH8nUPgcE
O6lRubeltlrTuDe7UJQ2nEPHcXjpUJJ8dxktyW+LovBy1OxW8g4GRAsmEJsoOEg0HuDdWcc4IshJ
PvwPJ7LblELAKsdkSt65y9VaklaEm7MlH4ImlgIa74TgRmutLUbWxM1QYhGE5rAzFhGU5i3RJOdx
L3N7GGGvLMW2z9NSHbIFX+/eNII9fNJ9nZbgLA==

`pragma protect key_keyowner="Metrics Technologies Inc.", key_keyname="DSim", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
Ti1NUgDv8YPk90APMwfu/mRr38QYwAxZfv0T6zQ89YS55t2EquEGVqrEafYX6rTydLOw8le1Oucv
f2oERpSSSTih/ScZneSZmuPE/Zh2BU1Ajv0j+/+0uEWXU+5lLPbDJjnapTmJXih1MYPf0SHpZZmE
BKj2IEBI9MPZlh6bxpa5BWJnyPdAvHf+UNaMXU9+pmbtrzUVebql4mFJu45Z3+ehmFY4FBW3zXMF
44C4TlHACLwL3vHVMCVfeKhgdVDbpE+/IFhTStz7mZ9h9RKGanQcs6YDVM1R+2RKA1QT1fX4FiQc
1V+FGmrm1ujxmFGXwpfNKByVlfCY0oWhRJCYYQ==

`pragma protect key_keyowner="Atrenta", key_keyname="ATR-SG-RSA-1", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=384)
`pragma protect key_block
HuEXFK0NXt09xU2yxxjng1OLsT+ZEM4EhqBgpr9D2ljw2vDaMBrqEsRQTc2B9soDq3ewDduHJXBd
OGYxkPnoN6LhjULtB2nTgjcH6NxA4puZ1ZNcndDndVBo8rTW5W1OqHq6InAG0CqPpTIkuqz3ECPl
EysI++MCDfH6tIzlekxJFIJ1McJsTq5rFuLzMMcrmkBxgcayDpOcCFuzZzCczxmt/cCCIKmDybwT
OQXmOcLJoYLP4sFu6R9c6xO8i6p++crv2N3eIxZHKbek9xBBZqQM9EYuEtsbkqAs9XZpa16i5njR
BDFxTKcP6r7JgFALJE89AZhBbate5JXWp0v4ECZD18aEL17CipwcWPutNMdG1apzSPP5y59n7rMG
yxBPz1gKHc3Emkl4WcO0hjICxqmO6dMXoY8JvBSf6ry2l0sH9Ihr3Bq5WWmlhPHnoaNr5jl//vNe
KfToWtn97eoVSt1LnmXXnSpdigbHr0UIg8AdkpdkuNRaWdVicDdgSo49

`pragma protect key_keyowner="Cadence Design Systems.", key_keyname="CDS_RSA_KEY_VER_1", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
mokwst2bn6UxD6V9UdIgCIG1QQ/d0FiJqYGOTI2eHPV6YElaLjnJ8DnQmZnGS95o3x93FDOoa58C
RwYsX1fVoVtXkj1LuZq0k7q9vEe4T8xMjpkeYtIHY9k0Xhy1Lq/xRlfzGAf9fvf9e+f4r7aR/Sb/
uCZxxugG5niTwLENY1n3NthYL0jvo8Fmdw4Qg0nTCGWlVCws+09K0g9/lx6I9EcuHHemcHO3fOZG
lMc4NaPNozKwnyDMoWUkwiVxyFEPFaQLNYqzjvR+CqrWfhFLo96JWhL+eaDoNuZoBVYQtNH5ZwBL
BoO27Pw10lgcReGlZBz3BLO7T4ddynCx0+eSnw==

`pragma protect key_keyowner="Synplicity", key_keyname="SYNP15_1", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
PiP7AjOQqqouyQMoBQqgWIDhUSViq94rIvGiIJ/UKMDspM/yXw1caE8AhWHTjYckC4yLpPAz5P6s
1Z6flzDPrzVwg4e59X2cc4IMCHhedna0rDO804njcc6amRDTeLsMLTkWfvomB4xwszm2AgT+PRnB
WHd09ZUDVFjiBXT+Oa9AicgGJHrX3w823yBPuAa704kje/SzgtiDpcTU1eLmLhLW7LpEd9KIHd9s
ER7Uk9Orws0Kq9PMTqMX4hMn5K5mFakOeOURiEbUjdv5RiIJ2g/PlQXSItM8fHsBTQa6fOaJwQTI
vHwK3a8ZBHpfT1YH+n7wNiNUZwD4SFXm1QVx4g==

`pragma protect key_keyowner="Mentor Graphics Corporation", key_keyname="MGC-PREC-RSA", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
Ul5ZfTHJwMctaNhYRortUZizYMPYRef7uYqPSuMkxsArnxI/cjGh+KRMwzV86hyp/6TXSJIjm5ec
2wX2UONdPN+DOJ84jYC4JbgJQrPnTj7ioD8uLX/WlyPcQzyF5keqFgj5eR5s13FskVWCuAWf5m9w
mhFEKFjVXDAr7gVgAJh/hL8P6Psrnf+LGfiM8JhnDepsHEYykGlpD3fzru2BGgqHWqPqFMcnyVGl
vysaIXiJz/eYKvO8RGcgd3DJAM/wPm9A0m/DWcmSnczOgTjoqkHcBg2H5uJMLvufzmjImi6LYEqq
v04ESDEN31cSUzqUYcayvMFOnI/WNsWbFIa5+Q==

`pragma protect data_method = "AES128-CBC"
`pragma protect encoding = (enctype = "BASE64", line_length = 76, bytes = 26560)
`pragma protect data_block
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
`pragma protect end_protected
`ifndef GLBL
`define GLBL
`timescale  1 ps / 1 ps

module glbl ();

    parameter ROC_WIDTH = 100000;
    parameter TOC_WIDTH = 0;
    parameter GRES_WIDTH = 10000;
    parameter GRES_START = 10000;

//--------   STARTUP Globals --------------
    wire GSR;
    wire GTS;
    wire GWE;
    wire PRLD;
    wire GRESTORE;
    tri1 p_up_tmp;
    tri (weak1, strong0) PLL_LOCKG = p_up_tmp;

    wire PROGB_GLBL;
    wire CCLKO_GLBL;
    wire FCSBO_GLBL;
    wire [3:0] DO_GLBL;
    wire [3:0] DI_GLBL;
   
    reg GSR_int;
    reg GTS_int;
    reg PRLD_int;
    reg GRESTORE_int;

//--------   JTAG Globals --------------
    wire JTAG_TDO_GLBL;
    wire JTAG_TCK_GLBL;
    wire JTAG_TDI_GLBL;
    wire JTAG_TMS_GLBL;
    wire JTAG_TRST_GLBL;

    reg JTAG_CAPTURE_GLBL;
    reg JTAG_RESET_GLBL;
    reg JTAG_SHIFT_GLBL;
    reg JTAG_UPDATE_GLBL;
    reg JTAG_RUNTEST_GLBL;

    reg JTAG_SEL1_GLBL = 0;
    reg JTAG_SEL2_GLBL = 0 ;
    reg JTAG_SEL3_GLBL = 0;
    reg JTAG_SEL4_GLBL = 0;

    reg JTAG_USER_TDO1_GLBL = 1'bz;
    reg JTAG_USER_TDO2_GLBL = 1'bz;
    reg JTAG_USER_TDO3_GLBL = 1'bz;
    reg JTAG_USER_TDO4_GLBL = 1'bz;

    assign (strong1, weak0) GSR = GSR_int;
    assign (strong1, weak0) GTS = GTS_int;
    assign (weak1, weak0) PRLD = PRLD_int;
    assign (strong1, weak0) GRESTORE = GRESTORE_int;

    initial begin
	GSR_int = 1'b1;
	PRLD_int = 1'b1;
	#(ROC_WIDTH)
	GSR_int = 1'b0;
	PRLD_int = 1'b0;
    end

    initial begin
	GTS_int = 1'b1;
	#(TOC_WIDTH)
	GTS_int = 1'b0;
    end

    initial begin 
	GRESTORE_int = 1'b0;
	#(GRES_START);
	GRESTORE_int = 1'b1;
	#(GRES_WIDTH);
	GRESTORE_int = 1'b0;
    end

endmodule
`endif
