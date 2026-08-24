`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/07/2026 10:37:41 AM
// Design Name: 
// Module Name: audio
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module audio(
    input logic clk,
    input logic reset,
    input logic [31:0] sound_cmd,
    output logic audio_pwm,
    output logic audio_sd
    );

localparam int SAMPLE_DIV = 12500;
localparam logic [10:0] LAST_SAMPLE_ADDR = 11'd2047;

logic [10:0] sample_addr;
logic [15:0] launch_sample_data;
logic [13:0] sample_divider;
logic [7:0] pwm_counter;
logic [7:0] pwm_sample;
logic [31:0] last_sound_cmd;
logic playing;

assign audio_sd = 1'b1;

start_audio_rom start_rom(
    .addra(sample_addr),
    .douta(launch_sample_data),
    .ena(1'b1),
    .clka(clk)
);

always_ff @(posedge clk) begin
    if (reset) begin
        sample_addr <= 11'd0;
        sample_divider <= 14'd0;
        pwm_counter <= 8'd0;
        pwm_sample <= 8'h80;
        last_sound_cmd <= 32'd0;
        playing <= 1'b0;
        audio_pwm <= 1'b0;
    end else begin
        pwm_counter <= pwm_counter + 8'd1;
        audio_pwm <= pwm_counter < pwm_sample;

        if (sound_cmd != last_sound_cmd) begin
            last_sound_cmd <= sound_cmd;
            if (sound_cmd != 32'd0) begin
                sample_addr <= 11'd0;
                sample_divider <= 14'd0;
                pwm_sample <= 8'h80;
                playing <= 1'b1;
            end
        end

        if (playing) begin
            if (sample_divider == SAMPLE_DIV - 1) begin
                sample_divider <= 14'd0;
                pwm_sample <= launch_sample_data[15:8];

                if (sample_addr == LAST_SAMPLE_ADDR) begin
                    playing <= 1'b0;
                    pwm_sample <= 8'h80;
                end else begin
                    sample_addr <= sample_addr + 11'd1;
                end
            end else begin
                sample_divider <= sample_divider + 14'd1;
            end
        end else begin
            pwm_sample <= 8'h80;
        end
    end
end

endmodule
