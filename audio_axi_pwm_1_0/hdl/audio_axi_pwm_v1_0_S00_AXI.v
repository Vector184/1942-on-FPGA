`timescale 1 ns / 1 ps

module audio_axi_pwm_v1_0_S00_AXI #
(
    // Width of S_AXI data bus
    parameter integer C_S_AXI_DATA_WIDTH = 32,
    // Width of S_AXI address bus
    parameter integer C_S_AXI_ADDR_WIDTH = 6
)
(
    // User port: connect this to the external audio PWM pin in the top IP
    output wire audio_pwm_out,

    // Global Clock Signal
    input wire S_AXI_ACLK,
    // Global Reset Signal. This Signal is Active LOW
    input wire S_AXI_ARESETN,

    // AXI4-Lite slave interface
    input wire [C_S_AXI_ADDR_WIDTH-1 : 0] S_AXI_AWADDR,
    input wire [2 : 0] S_AXI_AWPROT,
    input wire S_AXI_AWVALID,
    output wire S_AXI_AWREADY,

    input wire [C_S_AXI_DATA_WIDTH-1 : 0] S_AXI_WDATA,
    input wire [(C_S_AXI_DATA_WIDTH/8)-1 : 0] S_AXI_WSTRB,
    input wire S_AXI_WVALID,
    output wire S_AXI_WREADY,

    output wire [1 : 0] S_AXI_BRESP,
    output wire S_AXI_BVALID,
    input wire S_AXI_BREADY,

    input wire [C_S_AXI_ADDR_WIDTH-1 : 0] S_AXI_ARADDR,
    input wire [2 : 0] S_AXI_ARPROT,
    input wire S_AXI_ARVALID,
    output wire S_AXI_ARREADY,

    output wire [C_S_AXI_DATA_WIDTH-1 : 0] S_AXI_RDATA,
    output wire [1 : 0] S_AXI_RRESP,
    output wire S_AXI_RVALID,
    input wire S_AXI_RREADY
);

    // =============================================================
    // AXI4-Lite signals
    // =============================================================
    reg [C_S_AXI_ADDR_WIDTH-1 : 0] axi_awaddr;
    reg axi_awready;
    reg axi_wready;
    reg [1 : 0] axi_bresp;
    reg axi_bvalid;
    reg [C_S_AXI_ADDR_WIDTH-1 : 0] axi_araddr;
    reg axi_arready;
    reg [C_S_AXI_DATA_WIDTH-1 : 0] axi_rdata;
    reg [1 : 0] axi_rresp;
    reg axi_rvalid;

    localparam integer ADDR_LSB = (C_S_AXI_DATA_WIDTH/32) + 1; // 2 for 32-bit AXI
    localparam integer OPT_MEM_ADDR_BITS = 3;                 // 16 registers

    wire slv_reg_rden;
    wire slv_reg_wren;
    reg [C_S_AXI_DATA_WIDTH-1:0] reg_data_out;
    integer byte_index;
    reg aw_en;

    assign S_AXI_AWREADY = axi_awready;
    assign S_AXI_WREADY  = axi_wready;
    assign S_AXI_BRESP   = axi_bresp;
    assign S_AXI_BVALID  = axi_bvalid;
    assign S_AXI_ARREADY = axi_arready;
    assign S_AXI_RDATA   = axi_rdata;
    assign S_AXI_RRESP   = axi_rresp;
    assign S_AXI_RVALID  = axi_rvalid;

    // =============================================================
    // Register map
    // =============================================================
    // 0x00 slv_reg0  CONTROL: bit0 = global audio enable
    // 0x04 slv_reg1  STATUS:  read-only summary status
    // 0x08 slv_reg2  SAMPLE_RATE_DIV, example: 100 MHz / 44100 = 2268
    // 0x0C slv_reg3  GLOBAL_VOLUME, 0-255
    //
    // 0x10 slv_reg4  CH0_SAMPLE write port, signed 16-bit PCM in [15:0]
    // 0x14 slv_reg5  CH0_CONTROL: bit0 = channel enable
    // 0x18 slv_reg6  CH0_VOLUME, 0-255
    // 0x1C slv_reg7  CH0_STATUS, read-only
    //
    // 0x20 slv_reg8  CH1_SAMPLE write port
    // 0x24 slv_reg9  CH1_CONTROL
    // 0x28 slv_reg10 CH1_VOLUME
    // 0x2C slv_reg11 CH1_STATUS, read-only
    //
    // 0x30 slv_reg12 CH2_SAMPLE write port
    // 0x34 slv_reg13 CH2_CONTROL
    // 0x38 slv_reg14 CH2_VOLUME
    // 0x3C slv_reg15 CH2_STATUS, read-only

    reg [C_S_AXI_DATA_WIDTH-1:0] slv_reg0;
    reg [C_S_AXI_DATA_WIDTH-1:0] slv_reg2;
    reg [C_S_AXI_DATA_WIDTH-1:0] slv_reg3;
    reg [C_S_AXI_DATA_WIDTH-1:0] slv_reg5;
    reg [C_S_AXI_DATA_WIDTH-1:0] slv_reg6;
    reg [C_S_AXI_DATA_WIDTH-1:0] slv_reg9;
    reg [C_S_AXI_DATA_WIDTH-1:0] slv_reg10;
    reg [C_S_AXI_DATA_WIDTH-1:0] slv_reg13;
    reg [C_S_AXI_DATA_WIDTH-1:0] slv_reg14;

    // =============================================================
    // 3 channel sample FIFOs
    // =============================================================
    localparam FIFO_DEPTH = 256;

    reg signed [15:0] fifo0 [0:FIFO_DEPTH-1];
    reg signed [15:0] fifo1 [0:FIFO_DEPTH-1];
    reg signed [15:0] fifo2 [0:FIFO_DEPTH-1];

    reg [7:0] wr0, rd0;
    reg [7:0] wr1, rd1;
    reg [7:0] wr2, rd2;

    // 9-bit count is needed because a 256-deep FIFO count ranges from 0 to 256.
    reg [8:0] count0;
    reg [8:0] count1;
    reg [8:0] count2;

    wire fifo0_full  = (count0 == FIFO_DEPTH);
    wire fifo1_full  = (count1 == FIFO_DEPTH);
    wire fifo2_full  = (count2 == FIFO_DEPTH);
    wire fifo0_empty = (count0 == 0);
    wire fifo1_empty = (count1 == 0);
    wire fifo2_empty = (count2 == 0);

    reg signed [15:0] ch0_sample;
    reg signed [15:0] ch1_sample;
    reg signed [15:0] ch2_sample;

    // =============================================================
    // Sample-rate generator
    // =============================================================
    reg [31:0] sample_counter;
    reg sample_tick;

    always @(posedge S_AXI_ACLK) begin
        if (S_AXI_ARESETN == 1'b0) begin
            sample_counter <= 32'd0;
            sample_tick    <= 1'b0;
        end else begin
            if (sample_counter >= slv_reg2) begin
                sample_counter <= 32'd0;
                sample_tick    <= 1'b1;
            end else begin
                sample_counter <= sample_counter + 1'b1;
                sample_tick    <= 1'b0;
            end
        end
    end

    // =============================================================
    // Mixer and PWM logic
    // =============================================================
    wire signed [23:0] ch0_scaled;
    wire signed [23:0] ch1_scaled;
    wire signed [23:0] ch2_scaled;

    wire signed [17:0] ch0_vol;
    wire signed [17:0] ch1_vol;
    wire signed [17:0] ch2_vol;

    wire signed [19:0] mix_sum;
    reg  signed [15:0] mixed_sample;
    wire [15:0] pwm_duty;

    wire signed [8:0] global_vol = {1'b0, slv_reg3[7:0]};
    wire signed [8:0] ch0_volume = {1'b0, slv_reg6[7:0]};
    wire signed [8:0] ch1_volume = {1'b0, slv_reg10[7:0]};
    wire signed [8:0] ch2_volume = {1'b0, slv_reg14[7:0]};

    // Per-channel volume: 0-255. A volume of 255 is approximately unity gain.
    assign ch0_scaled = ch0_sample * ch0_volume;
    assign ch1_scaled = ch1_sample * ch1_volume;
    assign ch2_scaled = ch2_sample * ch2_volume;

    assign ch0_vol = ch0_scaled >>> 8;
    assign ch1_vol = ch1_scaled >>> 8;
    assign ch2_vol = ch2_scaled >>> 8;

    // Sum three channels. If all three are loud, this may overflow, so saturate below.
    wire signed [19:0] raw_mix_sum = ch0_vol + ch1_vol + ch2_vol;
    wire signed [28:0] global_scaled_mix = raw_mix_sum * global_vol;
    assign mix_sum = global_scaled_mix >>> 8;

    always @(*) begin
        if (mix_sum > 20'sd32767)
            mixed_sample = 16'sd32767;
        else if (mix_sum < -20'sd32768)
            mixed_sample = -16'sd32768;
        else
            mixed_sample = mix_sum[15:0];
    end

    // Convert signed 16-bit PCM to unsigned PWM duty cycle.
    assign pwm_duty = mixed_sample + 16'h8000;

    reg [15:0] pwm_counter;
    reg audio_pwm_reg;
    assign audio_pwm_out = audio_pwm_reg;

    always @(posedge S_AXI_ACLK) begin
        if (S_AXI_ARESETN == 1'b0) begin
            pwm_counter   <= 16'd0;
            audio_pwm_reg <= 1'b0;
        end else begin
            pwm_counter <= pwm_counter + 1'b1;
            if (slv_reg0[0])
                audio_pwm_reg <= (pwm_counter < pwm_duty);
            else
                audio_pwm_reg <= 1'b0;
        end
    end

    // =============================================================
    // AXI write address ready
    // =============================================================
    always @(posedge S_AXI_ACLK) begin
        if (S_AXI_ARESETN == 1'b0) begin
            axi_awready <= 1'b0;
            aw_en       <= 1'b1;
        end else begin
            if (~axi_awready && S_AXI_AWVALID && S_AXI_WVALID && aw_en) begin
                axi_awready <= 1'b1;
                aw_en       <= 1'b0;
            end else if (S_AXI_BREADY && axi_bvalid) begin
                aw_en       <= 1'b1;
                axi_awready <= 1'b0;
            end else begin
                axi_awready <= 1'b0;
            end
        end
    end

    // AXI write address latch
    always @(posedge S_AXI_ACLK) begin
        if (S_AXI_ARESETN == 1'b0)
            axi_awaddr <= 0;
        else if (~axi_awready && S_AXI_AWVALID && S_AXI_WVALID && aw_en)
            axi_awaddr <= S_AXI_AWADDR;
    end

    // AXI write data ready
    always @(posedge S_AXI_ACLK) begin
        if (S_AXI_ARESETN == 1'b0) begin
            axi_wready <= 1'b0;
        end else begin
            if (~axi_wready && S_AXI_WVALID && S_AXI_AWVALID && aw_en)
                axi_wready <= 1'b1;
            else
                axi_wready <= 1'b0;
        end
    end

    assign slv_reg_wren = axi_wready && S_AXI_WVALID && axi_awready && S_AXI_AWVALID;

    wire [3:0] write_addr = axi_awaddr[ADDR_LSB+OPT_MEM_ADDR_BITS:ADDR_LSB];

    // =============================================================
    // AXI register writes + FIFO push + FIFO pop
    // Kept in one always block to avoid multiple drivers on FIFO counts.
    // =============================================================
    always @(posedge S_AXI_ACLK) begin
        if (S_AXI_ARESETN == 1'b0) begin
            slv_reg0  <= 32'd0;       // global enable off
            slv_reg2  <= 32'd2268;    // default 44.1 kHz at 100 MHz
            slv_reg3  <= 32'd255;     // global volume
            slv_reg5  <= 32'd0;       // CH0 disabled
            slv_reg6  <= 32'd255;     // CH0 volume
            slv_reg9  <= 32'd0;       // CH1 disabled
            slv_reg10 <= 32'd255;     // CH1 volume
            slv_reg13 <= 32'd0;       // CH2 disabled
            slv_reg14 <= 32'd255;     // CH2 volume

            wr0 <= 8'd0;
            rd0 <= 8'd0;
            wr1 <= 8'd0;
            rd1 <= 8'd0;
            wr2 <= 8'd0;
            rd2 <= 8'd0;

            count0 <= 9'd0;
            count1 <= 9'd0;
            count2 <= 9'd0;

            ch0_sample <= 16'sd0;
            ch1_sample <= 16'sd0;
            ch2_sample <= 16'sd0;
        end else begin
            // -----------------------------
            // Normal AXI writes
            // -----------------------------
            if (slv_reg_wren) begin
                case (write_addr)
                    4'h0: begin
                        for (byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1)
                            if (S_AXI_WSTRB[byte_index])
                                slv_reg0[(byte_index*8) +: 8] <= S_AXI_WDATA[(byte_index*8) +: 8];
                    end

                    4'h2: begin
                        for (byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1)
                            if (S_AXI_WSTRB[byte_index])
                                slv_reg2[(byte_index*8) +: 8] <= S_AXI_WDATA[(byte_index*8) +: 8];
                    end

                    4'h3: begin
                        for (byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1)
                            if (S_AXI_WSTRB[byte_index])
                                slv_reg3[(byte_index*8) +: 8] <= S_AXI_WDATA[(byte_index*8) +: 8];
                    end

                    // CH0 sample write pushes into FIFO0.
                    4'h4: begin
                        if (!fifo0_full) begin
                            fifo0[wr0] <= S_AXI_WDATA[15:0];
                            wr0 <= wr0 + 1'b1;
                            count0 <= count0 + 1'b1;
                        end
                    end

                    4'h5: begin
                        for (byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1)
                            if (S_AXI_WSTRB[byte_index])
                                slv_reg5[(byte_index*8) +: 8] <= S_AXI_WDATA[(byte_index*8) +: 8];
                    end

                    4'h6: begin
                        for (byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1)
                            if (S_AXI_WSTRB[byte_index])
                                slv_reg6[(byte_index*8) +: 8] <= S_AXI_WDATA[(byte_index*8) +: 8];
                    end

                    // CH1 sample write pushes into FIFO1.
                    4'h8: begin
                        if (!fifo1_full) begin
                            fifo1[wr1] <= S_AXI_WDATA[15:0];
                            wr1 <= wr1 + 1'b1;
                            count1 <= count1 + 1'b1;
                        end
                    end

                    4'h9: begin
                        for (byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1)
                            if (S_AXI_WSTRB[byte_index])
                                slv_reg9[(byte_index*8) +: 8] <= S_AXI_WDATA[(byte_index*8) +: 8];
                    end

                    4'hA: begin
                        for (byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1)
                            if (S_AXI_WSTRB[byte_index])
                                slv_reg10[(byte_index*8) +: 8] <= S_AXI_WDATA[(byte_index*8) +: 8];
                    end

                    // CH2 sample write pushes into FIFO2.
                    4'hC: begin
                        if (!fifo2_full) begin
                            fifo2[wr2] <= S_AXI_WDATA[15:0];
                            wr2 <= wr2 + 1'b1;
                            count2 <= count2 + 1'b1;
                        end
                    end

                    4'hD: begin
                        for (byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1)
                            if (S_AXI_WSTRB[byte_index])
                                slv_reg13[(byte_index*8) +: 8] <= S_AXI_WDATA[(byte_index*8) +: 8];
                    end

                    4'hE: begin
                        for (byte_index = 0; byte_index <= (C_S_AXI_DATA_WIDTH/8)-1; byte_index = byte_index+1)
                            if (S_AXI_WSTRB[byte_index])
                                slv_reg14[(byte_index*8) +: 8] <= S_AXI_WDATA[(byte_index*8) +: 8];
                    end

                    default: begin
                        // Read-only/status/sample-port registers are ignored here.
                    end
                endcase
            end

            // -----------------------------
            // FIFO pop at sample rate
            // -----------------------------
            if (sample_tick) begin
                if (slv_reg5[0] && !fifo0_empty) begin
                    ch0_sample <= fifo0[rd0];
                    rd0 <= rd0 + 1'b1;
                    count0 <= count0 - 1'b1;
                end else begin
                    ch0_sample <= 16'sd0;
                end

                if (slv_reg9[0] && !fifo1_empty) begin
                    ch1_sample <= fifo1[rd1];
                    rd1 <= rd1 + 1'b1;
                    count1 <= count1 - 1'b1;
                end else begin
                    ch1_sample <= 16'sd0;
                end

                if (slv_reg13[0] && !fifo2_empty) begin
                    ch2_sample <= fifo2[rd2];
                    rd2 <= rd2 + 1'b1;
                    count2 <= count2 - 1'b1;
                end else begin
                    ch2_sample <= 16'sd0;
                end
            end
        end
    end

    // =============================================================
    // AXI write response
    // =============================================================
    always @(posedge S_AXI_ACLK) begin
        if (S_AXI_ARESETN == 1'b0) begin
            axi_bvalid <= 1'b0;
            axi_bresp  <= 2'b0;
        end else begin
            if (axi_awready && S_AXI_AWVALID && ~axi_bvalid && axi_wready && S_AXI_WVALID) begin
                axi_bvalid <= 1'b1;
                axi_bresp  <= 2'b0; // OKAY
            end else if (S_AXI_BREADY && axi_bvalid) begin
                axi_bvalid <= 1'b0;
            end
        end
    end

    // =============================================================
    // AXI read address ready/latch
    // =============================================================
    always @(posedge S_AXI_ACLK) begin
        if (S_AXI_ARESETN == 1'b0) begin
            axi_arready <= 1'b0;
            axi_araddr  <= 0;
        end else begin
            if (~axi_arready && S_AXI_ARVALID) begin
                axi_arready <= 1'b1;
                axi_araddr  <= S_AXI_ARADDR;
            end else begin
                axi_arready <= 1'b0;
            end
        end
    end

    // AXI read valid/response
    always @(posedge S_AXI_ACLK) begin
        if (S_AXI_ARESETN == 1'b0) begin
            axi_rvalid <= 1'b0;
            axi_rresp  <= 2'b0;
        end else begin
            if (axi_arready && S_AXI_ARVALID && ~axi_rvalid) begin
                axi_rvalid <= 1'b1;
                axi_rresp  <= 2'b0; // OKAY
            end else if (axi_rvalid && S_AXI_RREADY) begin
                axi_rvalid <= 1'b0;
            end
        end
    end

    assign slv_reg_rden = axi_arready & S_AXI_ARVALID & ~axi_rvalid;

    wire [31:0] global_status = {
        20'd0,
        fifo2_full, fifo2_empty,
        fifo1_full, fifo1_empty,
        fifo0_full, fifo0_empty,
        slv_reg13[0], slv_reg9[0], slv_reg5[0], slv_reg0[0]
    };

    wire [31:0] ch0_status = {15'd0, count0, 6'd0, fifo0_full, fifo0_empty};
    wire [31:0] ch1_status = {15'd0, count1, 6'd0, fifo1_full, fifo1_empty};
    wire [31:0] ch2_status = {15'd0, count2, 6'd0, fifo2_full, fifo2_empty};

    // AXI register read mux
    always @(*) begin
        case (axi_araddr[ADDR_LSB+OPT_MEM_ADDR_BITS:ADDR_LSB])
            4'h0: reg_data_out = slv_reg0;
            4'h1: reg_data_out = global_status;
            4'h2: reg_data_out = slv_reg2;
            4'h3: reg_data_out = slv_reg3;
            4'h4: reg_data_out = 32'd0;       // sample write-only
            4'h5: reg_data_out = slv_reg5;
            4'h6: reg_data_out = slv_reg6;
            4'h7: reg_data_out = ch0_status;
            4'h8: reg_data_out = 32'd0;       // sample write-only
            4'h9: reg_data_out = slv_reg9;
            4'hA: reg_data_out = slv_reg10;
            4'hB: reg_data_out = ch1_status;
            4'hC: reg_data_out = 32'd0;       // sample write-only
            4'hD: reg_data_out = slv_reg13;
            4'hE: reg_data_out = slv_reg14;
            4'hF: reg_data_out = ch2_status;
            default: reg_data_out = 32'd0;
        endcase
    end

    // AXI read data output register
    always @(posedge S_AXI_ACLK) begin
        if (S_AXI_ARESETN == 1'b0)
            axi_rdata <= 0;
        else if (slv_reg_rden)
            axi_rdata <= reg_data_out;
    end

endmodule
