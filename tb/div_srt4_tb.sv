//=============================================================================
// div_srt4_tb.sv — SRT-4 Divider Testbench (Self-Checking)
//=============================================================================
// Tests:
//   Tier 1: Directed corner cases (divide-by-zero, overflow, sign combinations)
//   Tier 2: Powers of 2 exhaustive
//   Tier 3: Randomized 64-bit pairs (configurable count)
//   Protocol: back-to-back valid, ready_i backpressure
//   SVA: Handshake protocol assertions
//=============================================================================

`timescale 1ns / 1ps

module div_srt4_tb;

    import div_srt4_pkg::*;

    //=========================================================================
    // Parameters
    //=========================================================================
    localparam int CLK_PERIOD    = 10;         // 100 MHz simulation (not timing-critical)
    localparam int RANDOM_TESTS  = 100000;     // Random test count
    localparam int RANDOM_SEED   = 42;

    //=========================================================================
    // DUT Signals
    //=========================================================================
    logic                clk;
    logic                rst_n;
    logic                valid_i;
    logic                ready_o;
    logic [WIDTH-1:0]    dividend_i;
    logic [WIDTH-1:0]    divisor_i;
    logic                valid_o;
    logic                ready_i;
    logic [WIDTH-1:0]    quotient_o;
    logic [WIDTH-1:0]    remainder_o;
    logic                div_by_zero_o;
    logic                overflow_o;
    logic                busy_o;

    //=========================================================================
    // DUT Instantiation
    //=========================================================================
    div_srt4_top u_dut (
        .clk           (clk),
        .rst_n         (rst_n),
        .valid_i       (valid_i),
        .ready_o       (ready_o),
        .dividend_i    (dividend_i),
        .divisor_i     (divisor_i),
        .valid_o       (valid_o),
        .ready_i       (ready_i),
        .quotient_o    (quotient_o),
        .remainder_o   (remainder_o),
        .div_by_zero_o (div_by_zero_o),
        .overflow_o    (overflow_o),
        .busy_o        (busy_o)
    );

    //=========================================================================
    // Clock and Reset
    //=========================================================================
    initial clk = 1'b0;
    always #(CLK_PERIOD/2) clk = ~clk;

    initial begin
        rst_n = 1'b0;
        repeat (5) @(posedge clk);
        rst_n = 1'b1;
    end

    //=========================================================================
    // Reference Model
    //=========================================================================
    function automatic void ref_divide(
        input  logic [WIDTH-1:0] a, b,
        output logic [WIDTH-1:0] q_ref, r_ref,
        output logic             dbz_ref, ovf_ref
    );
        logic signed [WIDTH-1:0] a_s, b_s, q_s, r_s;
        a_s = a;
        b_s = b;

        dbz_ref = 1'b0;
        ovf_ref = 1'b0;
        q_ref   = '0;
        r_ref   = '0;

        if (b == '0) begin
            dbz_ref = 1'b1;
            q_ref = '1;
            r_ref = a;
        end else if (a == 64'h8000000000000000 && b == 64'hFFFFFFFFFFFFFFFF) begin
            ovf_ref = 1'b1;
            q_ref = 64'h8000000000000000;
            r_ref = '0;
        end else begin
            q_s = a_s / b_s;
            r_s = a_s % b_s;
            q_ref = q_s;
            r_ref = r_s;
        end
    endfunction

    //=========================================================================
    // Test Infrastructure
    //=========================================================================
    int       test_count;
    int       pass_count;
    int       fail_count;
    string    test_name;

    task automatic start_test(input string name);
        test_name  = name;
        test_count = test_count + 1;
        $display("[TEST %0d] %s", test_count, name);
    endtask

    //=========================================================================
    // Send one division operation to DUT
    //=========================================================================
    task automatic send_division(
        input logic [WIDTH-1:0] dividend,
        input logic [WIDTH-1:0] divisor,
        input int               ready_delay  // cycles to hold ready_i low after valid_o
    );
        // Wait for ready_o and send operands
        while (!ready_o) @(posedge clk);
        valid_i   = 1'b1;
        dividend_i = dividend;
        divisor_i  = divisor;
        @(posedge clk);
        valid_i   = 1'b0;

        // Wait for valid_o
        while (!valid_o) @(posedge clk);

        // Apply backpressure if specified
        if (ready_delay > 0) begin
            repeat (ready_delay) @(posedge clk);
        end
        ready_i = 1'b1;
        @(posedge clk);
        ready_i = 1'b0;
    endtask

    //=========================================================================
    // Check result against reference model
    //=========================================================================
    function automatic bit check_result(
        input logic [WIDTH-1:0] dividend, divisor,
        input logic [WIDTH-1:0] q_rtl, r_rtl,
        input logic             dbz_rtl, ovf_rtl
    );
        logic [WIDTH-1:0] q_ref, r_ref;
        logic             dbz_ref, ovf_ref;

        ref_divide(dividend, divisor, q_ref, r_ref, dbz_ref, ovf_ref);

        if (dbz_rtl !== dbz_ref) begin
            $display("  FAIL: div_by_zero mismatch. RTL=%b REF=%b | %d / %d",
                     dbz_rtl, dbz_ref, $signed(dividend), $signed(divisor));
            return 1'b0;
        end
        if (ovf_rtl !== ovf_ref) begin
            $display("  FAIL: overflow mismatch. RTL=%b REF=%b | %d / %d",
                     ovf_rtl, ovf_ref, $signed(dividend), $signed(divisor));
            return 1'b0;
        end
        if (!dbz_ref && !ovf_ref) begin
            if (q_rtl !== q_ref) begin
                $display("  FAIL: quotient mismatch. RTL=%d REF=%d | %d / %d",
                         $signed(q_rtl), $signed(q_ref),
                         $signed(dividend), $signed(divisor));
                return 1'b0;
            end
            if (r_rtl !== r_ref) begin
                $display("  FAIL: remainder mismatch. RTL=%d REF=%d | %d / %d",
                         $signed(r_rtl), $signed(r_ref),
                         $signed(dividend), $signed(divisor));
                return 1'b0;
            end
        end
        return 1'b1;
    endfunction

    //=========================================================================
    // Run one test case
    //=========================================================================
    task automatic run_case(
        input logic [WIDTH-1:0] dividend,
        input logic [WIDTH-1:0] divisor,
        input int               backpressure
    );
        send_division(dividend, divisor, backpressure);

        if (check_result(dividend, divisor,
                         quotient_o, remainder_o, div_by_zero_o, overflow_o))
            pass_count = pass_count + 1;
        else
            fail_count = fail_count + 1;
    endtask

    //=========================================================================
    // MAIN TEST SEQUENCE
    //=========================================================================
    initial begin
        test_count  = 0;
        pass_count  = 0;
        fail_count  = 0;
        valid_i     = 1'b0;
        ready_i     = 1'b0;
        dividend_i  = '0;
        divisor_i   = '0;

        // Wait for reset
        @(posedge rst_n);
        repeat (3) @(posedge clk);

        //=====================================================================
        // TIER 1: Directed Corner Cases
        //=====================================================================
        start_test("Tier 1: Directed Corner Cases");

        // Divide by zero
        run_case(64'd100, 64'd0, 0);
        run_case(64'd0,   64'd0, 0);
        run_case(-64'd1,  64'd0, 0);

        // INT64_MIN / -1 (overflow)
        run_case(64'h8000000000000000, 64'hFFFFFFFFFFFFFFFF, 0);

        // 0 / X
        run_case(64'd0, 64'd5, 0);
        run_case(64'd0, -64'd5, 0);
        run_case(64'd0, 64'd1, 0);

        // X / 1
        run_case(64'd100, 64'd1, 0);
        run_case(-64'd100, 64'd1, 0);
        run_case(64'h8000000000000000, 64'd1, 0);       // INT64_MIN / 1

        // X / -1
        run_case(64'd100, -64'd1, 0);
        run_case(-64'd100, -64'd1, 0);
        run_case(64'h7FFFFFFFFFFFFFFF, -64'd1, 0);       // INT64_MAX / -1

        // dividend == divisor
        run_case(64'd42, 64'd42, 0);
        run_case(-64'd42, -64'd42, 0);

        // dividend == -divisor
        run_case(64'd42, -64'd42, 0);
        run_case(-64'd42, 64'd42, 0);

        // Sign combinations
        run_case( 64'd100,  64'd7, 0);   // + / +
        run_case(-64'd100,  64'd7, 0);   // - / +
        run_case( 64'd100, -64'd7, 0);   // + / -
        run_case(-64'd100, -64'd7, 0);   // - / -

        // INT64_MAX, INT64_MIN cases
        run_case(64'h7FFFFFFFFFFFFFFF,  64'd2, 0);        // INT64_MAX / 2
        run_case(64'h7FFFFFFFFFFFFFFF, -64'd2, 0);
        run_case(64'h8000000000000000,  64'd2, 0);        // INT64_MIN / 2
        run_case(64'h8000000000000000, -64'd2, 0);

        // Boundary values
        run_case(64'd1, 64'd1, 0);
        run_case(64'd1, -64'd1, 0);
        run_case(-64'd1, 64'd1, 0);
        run_case(-64'd1, -64'd1, 0);

        $display("  Tier 1 complete: %0d pass, %0d fail", pass_count, fail_count);

        //=====================================================================
        // TIER 2: Powers of 2 (exhaustive)
        //=====================================================================
        start_test("Tier 2: Powers of 2 (exhaustive)");

        for (int i = 0; i < 63; i++) begin
            for (int j = 0; j < 63; j++) begin
                automatic logic [WIDTH-1:0] divd = 64'd1 << i;
                automatic logic [WIDTH-1:0] divs = 64'd1 << j;
                run_case( divd,  divs, 0);
                run_case( divd, -divs, 0);
                run_case(-divd,  divs, 0);
                run_case(-divd, -divs, 0);
            end
        end
        $display("  Tier 2 complete: %0d pass, %0d fail", pass_count, fail_count);

        //=====================================================================
        // TIER 3: Randomized Tests
        //=====================================================================
        start_test("Tier 3: Randomized Tests");
        $display("  Running %0d random test vectors...", RANDOM_TESTS);

        for (int k = 0; k < RANDOM_TESTS; k++) begin
            automatic logic [WIDTH-1:0] rand_a, rand_b;
            rand_a = $urandom_range(0, 2**WIDTH-1);
            rand_b = $urandom_range(0, 2**WIDTH-1);
            run_case(rand_a, rand_b, 0);

            if (k > 0 && (k % 10000 == 0))
                $display("    %0d tests done (%0d pass, %0d fail)", k, pass_count, fail_count);
        end
        $display("  Tier 3 complete: %0d pass, %0d fail", pass_count, fail_count);

        //=====================================================================
        // TIER 4: Protocol Stress Tests
        //=====================================================================
        start_test("Tier 4: Protocol Stress (backpressure)");

        // Back-to-back with ready_i backpressure
        for (int k = 0; k < 20; k++) begin
            automatic logic [WIDTH-1:0] rand_a, rand_b;
            rand_a = $urandom_range(0, 2**WIDTH-1);
            rand_b = $urandom_range(0, 2**WIDTH-1);
            run_case(rand_a, rand_b, $urandom_range(1, 5));
        end
        $display("  Tier 4 complete: %0d pass, %0d fail", pass_count, fail_count);

        //=====================================================================
        // SUMMARY
        //=====================================================================
        $display("============================================================");
        $display("TEST SUMMARY: %0d total, %0d PASS, %0d FAIL",
                 test_count, pass_count, fail_count);
        if (fail_count == 0)
            $display("ALL TESTS PASSED!");
        else
            $display("SOME TESTS FAILED!");
        $display("============================================================");

        $finish;
    end

    //=========================================================================
    // Timeout watchdog
    //=========================================================================
    initial begin
        #(CLK_PERIOD * 1000000);  // 10 ms timeout
        $display("TIMEOUT: Simulation exceeded limit");
        $finish;
    end

    //=========================================================================
    // SVA: Handshake Protocol Assertions
    //=========================================================================
    // Output data stable until accepted
    property p_output_stable;
        @(posedge clk) disable iff (!rst_n)
        (valid_o && !ready_i) |=> $stable(quotient_o) && $stable(remainder_o)
                               && $stable(div_by_zero_o) && $stable(overflow_o);
    endproperty
    a_output_stable: assert property (p_output_stable);

    // busy_o asserted from IDLE exit until output handshake complete
    property p_busy_duration;
        @(posedge clk) disable iff (!rst_n)
        $rose(busy_o) |-> busy_o throughout (valid_o && ready_i)[->1];
    endproperty
    a_busy_duration: assert property (p_busy_duration);

    // ready_o asserted only in IDLE
    property p_ready_in_idle;
        @(posedge clk) disable iff (!rst_n)
        ready_o |-> (u_dut.state_q == ST_IDLE);
    endproperty
    a_ready_in_idle: assert property (p_ready_in_idle);

    // valid_o not asserted during IDLE
    property p_valid_not_idle;
        @(posedge clk) disable iff (!rst_n)
        valid_o |-> (u_dut.state_q != ST_IDLE);
    endproperty
    a_valid_not_idle: assert property (p_valid_not_idle);

    // Iteration count bounded
    property p_iter_bound;
        @(posedge clk) disable iff (!rst_n)
        (u_dut.state_q == ST_ITERATE) |-> (u_dut.u_datapath.iter_cnt_q < ITER_CNT);
    endproperty
    a_iter_bound: assert property (p_iter_bound);

endmodule