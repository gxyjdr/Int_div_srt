//=============================================================================
// sim/sim_main.cpp — SRT-4 Divider C++ Testbench (Verilator)
//=============================================================================

#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cassert>
#include <cstring>
#include <string>
#include "Vdiv_srt4_top.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

//=============================================================================
// Reference models
//=============================================================================
struct DivResult {
    uint64_t quotient;
    uint64_t remainder;
    bool     div_by_zero;
    bool     overflow;
};

DivResult ref_divide(int64_t dividend, int64_t divisor) {
    DivResult r = {0, 0, false, false};
    if (divisor == 0) {
        r.div_by_zero = true;
        r.quotient    = 0xFFFFFFFFFFFFFFFFULL;
        r.remainder   = (uint64_t)dividend;
    } else if (dividend == INT64_MIN && divisor == -1) {
        r.overflow  = true;
        r.quotient  = (uint64_t)INT64_MIN;
        r.remainder = 0;
    } else {
        r.quotient  = (uint64_t)(dividend / divisor);
        r.remainder = (uint64_t)(dividend % divisor);
    }
    return r;
}

DivResult uref_divide(uint64_t dividend, uint64_t divisor) {
    DivResult r = {0, 0, false, false};
    if (divisor == 0) {
        r.div_by_zero = true;
        r.quotient    = 0xFFFFFFFFFFFFFFFFULL;
        r.remainder   = dividend;
    } else {
        r.quotient  = dividend / divisor;
        r.remainder = dividend % divisor;
    }
    return r;
}

//=============================================================================
// DUT interface
//=============================================================================
class DutDriver {
public:
    Vdiv_srt4_top *dut;
    uint64_t       sim_time;
    VerilatedVcdC *trace;
    bool           trace_enabled;

    DutDriver() {
        Verilated::traceEverOn(true);
        dut = new Vdiv_srt4_top;
        sim_time = 0;
        trace = nullptr;
        trace_enabled = false;
        dut->clk = 0;
        dut->rst_n = 0;
        dut->valid_i = 0;
        dut->ready_i = 0;
        dut->dividend_i = 0;
        dut->divisor_i  = 0;
        dut->signed_op_i = 0;
    }

    ~DutDriver() {
        if (trace) { trace->close(); delete trace; }
        delete dut;
    }

    void open_trace(const std::string &path) {
        if (trace) { trace->close(); delete trace; trace = nullptr; }
        trace = new VerilatedVcdC;
        dut->trace(trace, 99);
        trace->open(path.c_str());
        trace_enabled = true;
    }

    void close_trace() {
        if (trace) { trace->flush(); trace->close(); delete trace; trace = nullptr; }
        trace_enabled = false;
    }

    void tick() {
        dut->clk = 0; dut->eval();
        if (trace_enabled) trace->dump(sim_time * 10 + 0);
        dut->clk = 1; dut->eval();
        if (trace_enabled) trace->dump(sim_time * 10 + 5);
        sim_time++;
    }

    void reset() {
        dut->rst_n = 0;
        for (int i = 0; i < 5; i++) tick();
        dut->rst_n = 1;
    }

    // Send one division, wait for result. Returns true on success.
    bool run_division(uint64_t dividend, uint64_t divisor,
                      uint64_t &q_out, uint64_t &r_out,
                      bool &dbz_out, bool &ovf_out,
                      bool signed_op = true) {
        // Wait for ready
        while (!dut->ready_o) tick();

        // Send operands
        dut->valid_i    = 1;
        dut->dividend_i = dividend;
        dut->divisor_i  = divisor;
        dut->signed_op_i = signed_op;
        tick();
        dut->valid_i = 0;

        // Wait for valid
        int timeout = 1000;
        while (!dut->valid_o && --timeout) tick();
        if (timeout == 0) {
            printf("TIMEOUT waiting for valid_o\n");
            return false;
        }

        // Accept result
        dut->ready_i = 1;
        tick();
        dut->ready_i = 0;

        q_out   = dut->quotient_o;
        r_out   = dut->remainder_o;
        dbz_out = dut->div_by_zero_o;
        ovf_out = dut->overflow_o;
        return true;
    }
};

//=============================================================================
// Check helpers
//=============================================================================
int pass_cnt = 0;
int fail_cnt = 0;

bool check_result(const char *name, uint64_t dividend, uint64_t divisor,
                  uint64_t q_rtl, uint64_t r_rtl, bool dbz_rtl, bool ovf_rtl) {
    DivResult ref = ref_divide((int64_t)dividend, (int64_t)divisor);

    bool ok = true;
    if (dbz_rtl != ref.div_by_zero) {
        printf("  FAIL [%s] div_by_zero: RTL=%d REF=%d\n", name, dbz_rtl, ref.div_by_zero);
        ok = false;
    }
    if (ovf_rtl != ref.overflow) {
        printf("  FAIL [%s] overflow: RTL=%d REF=%d\n", name, ovf_rtl, ref.overflow);
        ok = false;
    }
    if (!ref.div_by_zero && !ref.overflow) {
        if (q_rtl != ref.quotient) {
            printf("  FAIL [%s] quotient: RTL=0x%016llx REF=0x%016llx  (%lld / %lld)\n",
                   name, (unsigned long long)q_rtl, (unsigned long long)ref.quotient,
                   (long long)(int64_t)dividend, (long long)(int64_t)divisor);
            ok = false;
        }
        if (r_rtl != ref.remainder) {
            printf("  FAIL [%s] remainder: RTL=0x%016llx REF=0x%016llx  (%lld / %lld)\n",
                   name, (unsigned long long)r_rtl, (unsigned long long)ref.remainder,
                   (long long)(int64_t)dividend, (long long)(int64_t)divisor);
            ok = false;
        }
    }

    return ok;
}

bool ucheck_result(const char *name, uint64_t dividend, uint64_t divisor,
                   uint64_t q_rtl, uint64_t r_rtl, bool dbz_rtl, bool ovf_rtl) {
    DivResult ref = uref_divide(dividend, divisor);
    (void)ovf_rtl;  // unsigned has no overflow

    bool ok = true;
    if (dbz_rtl != ref.div_by_zero) {
        printf("  FAIL [%s] div_by_zero: RTL=%d REF=%d\n", name, dbz_rtl, ref.div_by_zero);
        ok = false;
    }
    if (!ref.div_by_zero) {
        if (q_rtl != ref.quotient) {
            printf("  FAIL [%s] quotient: RTL=0x%016llx REF=0x%016llx  (0x%llx / 0x%llx)\n",
                   name, (unsigned long long)q_rtl, (unsigned long long)ref.quotient,
                   (unsigned long long)dividend, (unsigned long long)divisor);
            ok = false;
        }
        if (r_rtl != ref.remainder) {
            printf("  FAIL [%s] remainder: RTL=0x%016llx REF=0x%016llx\n",
                   name, (unsigned long long)r_rtl, (unsigned long long)ref.remainder);
            ok = false;
        }
    }

    return ok;
}

void check_case(const char *name, uint64_t dividend, uint64_t divisor, bool do_trace = false) {
    static DutDriver dut_driver;
    static bool initialized = false;
    if (!initialized) { dut_driver.reset(); initialized = true; }

    if (do_trace) {
        char path[256];
        snprintf(path, sizeof(path), "wave_%s.vcd", name);
        dut_driver.open_trace(path);
    }

    uint64_t q_rtl, r_rtl;
    bool dbz_rtl, ovf_rtl;

    if (!dut_driver.run_division(dividend, divisor, q_rtl, r_rtl, dbz_rtl, ovf_rtl)) {
        fail_cnt++;
        dut_driver.close_trace();
        return;
    }

    if (do_trace) {
        dut_driver.close_trace();
    }

    bool ok = check_result(name, dividend, divisor, q_rtl, r_rtl, dbz_rtl, ovf_rtl);
    if (ok) pass_cnt++; else fail_cnt++;
}

//=============================================================================
// Standalone test runners
//=============================================================================

int run_cycles(uint64_t a, uint64_t b) {
    DutDriver dut_driver;
    dut_driver.open_trace("wave_cycles.vcd");
    dut_driver.reset();

    while (!dut_driver.dut->ready_o) dut_driver.tick();
    uint64_t t_handshake = dut_driver.sim_time;

    dut_driver.dut->valid_i     = 1;
    dut_driver.dut->dividend_i  = a;
    dut_driver.dut->divisor_i   = b;
    dut_driver.dut->signed_op_i = 1;
    dut_driver.tick();
    dut_driver.dut->valid_i = 0;

    int busy_cycles = 0;
    int timeout = 1000;
    while (!dut_driver.dut->valid_o && --timeout) {
        dut_driver.tick();
        busy_cycles++;
    }
    uint64_t t_valid_o = dut_driver.sim_time;

    dut_driver.dut->ready_i = 1;
    dut_driver.tick();
    dut_driver.dut->ready_i = 0;

    uint64_t q = dut_driver.dut->quotient_o;
    uint64_t r = dut_driver.dut->remainder_o;
    dut_driver.close_trace();

    DivResult ref = ref_divide((int64_t)a, (int64_t)b);
    bool ok = (q == ref.quotient) && (r == ref.remainder);

    printf("============================================================\n");
    printf("CYCLES report for %lld / %lld\n",
           (long long)(int64_t)a, (long long)(int64_t)b);
    printf("------------------------------------------------------------\n");
    printf("  Handshake-in cycle  : %llu\n", (unsigned long long)t_handshake);
    printf("  valid_o cycle       : %llu\n", (unsigned long long)t_valid_o);
    printf("  Busy (accept->valid): %d cycles\n", busy_cycles);
    printf("  Quotient  RTL/REF   : %lld / %lld\n",
           (long long)(int64_t)q, (long long)(int64_t)ref.quotient);
    printf("  Remainder RTL/REF   : %lld / %lld\n",
           (long long)(int64_t)r, (long long)(int64_t)ref.remainder);
    printf("  Match               : %s\n", ok ? "YES" : "NO");
    printf("============================================================\n");
    return ok ? 0 : 1;
}

int run_wave100() {
    DutDriver dut_driver;
    uint64_t q_rtl, r_rtl;
    bool dbz_rtl, ovf_rtl;

    pass_cnt = 0;
    fail_cnt = 0;
    srand(42);

    dut_driver.open_trace("wave_69_10_plus_99_random.vcd");
    dut_driver.reset();

    for (int k = 0; k < 100; k++) {
        uint64_t a;
        uint64_t b;
        char name[32];

        if (k == 0) {
            a = 69;
            b = 10;
            snprintf(name, sizeof(name), "case_%03d_69_div_10", k);
        } else {
            a = ((uint64_t)rand() << 32) | (uint64_t)rand();
            b = ((uint64_t)rand() << 32) | (uint64_t)rand();
            if (b == 0) b = 1;
            snprintf(name, sizeof(name), "case_%03d_random", k);
        }

        if (!dut_driver.run_division(a, b, q_rtl, r_rtl, dbz_rtl, ovf_rtl)) {
            fail_cnt++;
            continue;
        }

        bool ok = check_result(name, a, b, q_rtl, r_rtl, dbz_rtl, ovf_rtl);
        if (ok) pass_cnt++; else fail_cnt++;
    }

    dut_driver.close_trace();

    printf("============================================================\n");
    printf("WAVE100: %d tests, %d PASS, %d FAIL\n", pass_cnt + fail_cnt, pass_cnt, fail_cnt);
    printf("VCD: wave_69_10_plus_99_random.vcd\n");
    printf("============================================================\n");

    return fail_cnt ? 1 : 0;
}

int run_unsigned_msb1() {
    DutDriver dut_driver;
    dut_driver.reset();
    int upass = 0, ufail = 0;

    struct Case { const char *name; uint64_t a; uint64_t b; };
    Case cases[] = {
        {"u_all_ones_div_3",      0xFFFFFFFFFFFFFFFFULL, 3},
        {"u_all_ones_div_7",      0xFFFFFFFFFFFFFFFFULL, 7},
        {"u_all_ones_div_10",     0xFFFFFFFFFFFFFFFFULL, 10},
        {"u_msb1_lsb1_div_3",     0x8000000000000001ULL, 3},
        {"u_msb1_lsb1_div_5",     0x8000000000000001ULL, 5},
        {"u_msb1_pattern_div_3",  0xA5A5A5A5A5A5A5A5ULL, 3},
        {"u_msb1_pattern_div_7",  0xDEADBEEFDEADBEEFULL, 7},
        {"u_msb1_div_msb1",       0xFFFFFFFFFFFFFFFFULL, 0x8000000000000001ULL},
        {"u_msb1_div_unsigned_2", 0xC000000000000001ULL, 2},
        {"u_msb1_div_unsigned_3", 0xC000000000000001ULL, 3},
        {"u_safe_max_div_3",      0x7FFFFFFFFFFFFFFFULL, 3},
    };

    printf("============================================================\n");
    printf("UNSIGNED MSB=1 Tests\n");
    printf("============================================================\n");

    for (auto &c : cases) {
        uint64_t q_rtl, r_rtl;
        bool dbz_rtl, ovf_rtl;
        if (!dut_driver.run_division(c.a, c.b, q_rtl, r_rtl,
                                     dbz_rtl, ovf_rtl, /*signed_op=*/false)) {
            ufail++;
            continue;
        }
        uint64_t q_ref = (c.b == 0) ? 0xFFFFFFFFFFFFFFFFULL : (c.a / c.b);
        uint64_t r_ref = (c.b == 0) ? c.a : (c.a % c.b);
        bool ok = (q_rtl == q_ref) && (r_rtl == r_ref);
        printf("  [%-28s] A=0x%016llx B=0x%016llx\n", c.name,
               (unsigned long long)c.a, (unsigned long long)c.b);
        printf("        Q  RTL=0x%016llx REF=0x%016llx  %s\n",
               (unsigned long long)q_rtl, (unsigned long long)q_ref,
               q_rtl == q_ref ? "OK" : "FAIL");
        printf("        R  RTL=0x%016llx REF=0x%016llx  %s\n",
               (unsigned long long)r_rtl, (unsigned long long)r_ref,
               r_rtl == r_ref ? "OK" : "FAIL");
        if (ok) upass++; else ufail++;
    }
    printf("============================================================\n");
    printf("UNSIGNED MSB=1: %d pass, %d fail\n", upass, ufail);
    printf("============================================================\n");
    pass_cnt += upass; fail_cnt += ufail;
    return ufail ? 1 : 0;
}

//=============================================================================
// Main
//=============================================================================
int main(int argc, char **argv) {
    if (argc > 1 && strcmp(argv[1], "unsigned") == 0) {
        return run_unsigned_msb1();
    }
    if (argc > 1 && strcmp(argv[1], "cycles") == 0) {
        uint64_t a = 97, b = 10;
        if (argc >= 4) { a = strtoull(argv[2], nullptr, 0); b = strtoull(argv[3], nullptr, 0); }
        return run_cycles(a, b);
    }
    if (argc > 1 && strcmp(argv[1], "wave100") == 0) {
        return run_wave100();
    }

    printf("============================================================\n");
    printf("SRT-4 Divider Testbench (Verilator)\n");
    printf("============================================================\n\n");

    //---------------------------------------------------------------------
    // Tier 1: Directed Corner Cases
    //---------------------------------------------------------------------
    printf("[Tier 1] Directed Corner Cases (with VCD dump)\n");

    check_case("div_by_zero_pos",  100, 0, true);
    check_case("div_by_zero_zero", 0, 0, true);
    check_case("div_by_zero_neg",  (uint64_t)-1LL, 0, true);

    check_case("int64_min_div_neg1", (uint64_t)INT64_MIN, (uint64_t)-1LL, true);

    check_case("zero_div_pos", 0, 5, true);
    check_case("zero_div_neg", 0, (uint64_t)-5LL, true);
    check_case("zero_div_1",   0, 1, true);

    check_case("pos_div_1",  100, 1, true);
    check_case("neg_div_1",  (uint64_t)-100LL, 1, true);
    check_case("int64_min_div_1", (uint64_t)INT64_MIN, 1, true);

    check_case("pos_div_neg1",  100, (uint64_t)-1LL, true);
    check_case("neg_div_neg1",  (uint64_t)-100LL, (uint64_t)-1LL, true);
    check_case("int64_max_div_neg1", INT64_MAX, (uint64_t)-1LL, true);

    check_case("same_pos",  42, 42, true);
    check_case("same_neg",  (uint64_t)-42LL, (uint64_t)-42LL, true);
    check_case("opposite_1", 42, (uint64_t)-42LL, true);
    check_case("opposite_2", (uint64_t)-42LL, 42, true);

    check_case("pos_pos",  100, 7, true);
    check_case("neg_pos",  (uint64_t)-100LL, 7, true);
    check_case("pos_neg",  100, (uint64_t)-7LL, true);
    check_case("neg_neg",  (uint64_t)-100LL, (uint64_t)-7LL, true);

    check_case("int64_max_div_2",  INT64_MAX, 2, true);
    check_case("int64_max_div_neg2", INT64_MAX, (uint64_t)-2LL, true);
    check_case("int64_min_div_2",  (uint64_t)INT64_MIN, 2, true);
    check_case("int64_min_div_neg2", (uint64_t)INT64_MIN, (uint64_t)-2LL, true);

    check_case("one_div_one",    1, 1, true);
    check_case("one_div_neg1", 1, (uint64_t)-1LL, true);
    check_case("neg1_div_1", (uint64_t)-1LL, 1, true);
    check_case("neg1_div_neg1", (uint64_t)-1LL, (uint64_t)-1LL, true);

    printf("  Tier 1 done: %d pass, %d fail\n\n", pass_cnt, fail_cnt);

    //---------------------------------------------------------------------
    // Tier 2: Powers of 2 exhaustive
    //---------------------------------------------------------------------
    printf("[Tier 2] Powers of 2 (exhaustive)\n");
    for (int i = 0; i < 63; i++) {
        for (int j = 0; j < 63; j++) {
            uint64_t dvd = 1ULL << i;
            uint64_t dvs = 1ULL << j;
            check_case("pow2_pp", dvd, dvs);
            check_case("pow2_pn", dvd, (uint64_t)(-(int64_t)dvs));
            check_case("pow2_np", (uint64_t)(-(int64_t)dvd), dvs);
            check_case("pow2_nn", (uint64_t)(-(int64_t)dvd), (uint64_t)(-(int64_t)dvs));
        }
    }
    printf("  Tier 2 done: %d pass, %d fail\n\n", pass_cnt, fail_cnt);

    //---------------------------------------------------------------------
    // Tier 3: Randomized signed tests
    //---------------------------------------------------------------------
    printf("[Tier 3] Randomized Signed Tests\n");
    srand(42);
    const int RANDOM_COUNT = 10000;
    for (int k = 0; k < RANDOM_COUNT; k++) {
        uint64_t a = ((uint64_t)rand() << 32) | (uint64_t)rand();
        uint64_t b = ((uint64_t)rand() << 32) | (uint64_t)rand();
        if (b == 0) b = 1;
        check_case("rand", a, b);
    }
    printf("  Tier 3 done: %d pass, %d fail\n\n", pass_cnt, fail_cnt);

    //---------------------------------------------------------------------
    // Tier 4: Edge values
    //---------------------------------------------------------------------
    printf("[Tier 4] Edge Value Stress\n");
    check_case("max_div_2",  (uint64_t)INT64_MAX, 2);
    check_case("max_div_3",  (uint64_t)INT64_MAX, 3);
    check_case("min_div_2",  (uint64_t)INT64_MIN, 2);
    check_case("min_div_3",  (uint64_t)INT64_MIN, 3);
    check_case("small_div_1", (uint64_t)INT64_MAX, 1);
    check_case("small_div_2", (uint64_t)INT64_MAX, 2);
    check_case("small_div_3", (uint64_t)INT64_MAX, 3);
    check_case("small_div_4", (uint64_t)INT64_MIN, 1);
    check_case("small_div_5", (uint64_t)INT64_MIN, 2);

    printf("  Tier 4 done: %d pass, %d fail\n\n", pass_cnt, fail_cnt);

    //---------------------------------------------------------------------
    // Tier 5: Unsigned MSB=1 (previously failing cases)
    //---------------------------------------------------------------------
    printf("[Tier 5] Unsigned MSB=1 Corner Cases\n");
    run_unsigned_msb1();
    printf("\n");

    //---------------------------------------------------------------------
    // Tier 6: Unsigned random (new coverage)
    //---------------------------------------------------------------------
    printf("[Tier 6] Unsigned Random (including MSB=1)\n");
    {
        DutDriver udut;
        udut.reset();
        srand(12345);
        const int UCOUNT = 10000;
        int upass = 0, ufail = 0;
        for (int k = 0; k < UCOUNT; k++) {
            uint64_t a = ((uint64_t)rand() << 32) | (uint64_t)rand();
            uint64_t b = ((uint64_t)rand() << 32) | (uint64_t)rand();
            if (b == 0) b = 1;

            uint64_t q_rtl, r_rtl;
            bool dbz_rtl, ovf_rtl;
            char name[32];
            snprintf(name, sizeof(name), "urand_%05d", k);

            if (!udut.run_division(a, b, q_rtl, r_rtl, dbz_rtl, ovf_rtl, /*signed_op=*/false)) {
                ufail++;
                continue;
            }
            if (ucheck_result(name, a, b, q_rtl, r_rtl, dbz_rtl, ovf_rtl)) upass++;
            else ufail++;
        }
        pass_cnt += upass; fail_cnt += ufail;
        printf("  Tier 6 done: %d pass, %d fail\n\n", upass, ufail);
    }

    //---------------------------------------------------------------------
    // Summary
    //---------------------------------------------------------------------
    printf("============================================================\n");
    printf("TOTAL: %d tests, %d PASS, %d FAIL\n", pass_cnt + fail_cnt, pass_cnt, fail_cnt);
    if (fail_cnt == 0)
        printf("ALL TESTS PASSED!\n");
    else
        printf("SOME TESTS FAILED!\n");
    printf("============================================================\n");

    return fail_cnt ? 1 : 0;
}
