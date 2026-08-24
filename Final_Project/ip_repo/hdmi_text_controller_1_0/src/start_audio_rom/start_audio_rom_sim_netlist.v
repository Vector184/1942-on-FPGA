// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2022.2 (win64) Build 3671981 Fri Oct 14 05:00:03 MDT 2022
// Date        : Thu May  7 10:54:33 2026
// Host        : ECEB-3022-15 running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode funcsim
//               c:/Users/kakkar3/Desktop/Final_Project/ip_repo/hdmi_text_controller_1_0/src/start_audio_rom/start_audio_rom_sim_netlist.v
// Design      : start_audio_rom
// Purpose     : This verilog netlist is a functional simulation representation of the design and should not be modified
//               or synthesized. This netlist cannot be used for SDF annotated simulation.
// Device      : xc7s50csga324-1
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CHECK_LICENSE_TYPE = "start_audio_rom,blk_mem_gen_v8_4_5,{}" *) (* downgradeipidentifiedwarnings = "yes" *) (* x_core_info = "blk_mem_gen_v8_4_5,Vivado 2022.2" *) 
(* NotValidForBitStream *)
module start_audio_rom
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
  (* C_INIT_FILE = "start_audio_rom.mem" *) 
  (* C_INIT_FILE_NAME = "start_audio_rom.mif" *) 
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
  start_audio_rom_blk_mem_gen_v8_4_5 U0
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
`pragma protect encoding = (enctype = "BASE64", line_length = 76, bytes = 26480)
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
