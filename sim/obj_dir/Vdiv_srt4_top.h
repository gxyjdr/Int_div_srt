// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _VDIV_SRT4_TOP_H_
#define _VDIV_SRT4_TOP_H_  // guard

#include "verilated.h"

//==========

class Vdiv_srt4_top__Syms;
class Vdiv_srt4_top_VerilatedVcd;


//----------

VL_MODULE(Vdiv_srt4_top) {
  public:
    
    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    VL_IN8(clk,0,0);
    VL_IN8(rst_n,0,0);
    VL_IN8(valid_i,0,0);
    VL_OUT8(ready_o,0,0);
    VL_IN8(signed_op_i,0,0);
    VL_OUT8(valid_o,0,0);
    VL_IN8(ready_i,0,0);
    VL_OUT8(div_by_zero_o,0,0);
    VL_OUT8(overflow_o,0,0);
    VL_OUT8(busy_o,0,0);
    VL_IN64(dividend_i,63,0);
    VL_IN64(divisor_i,63,0);
    VL_OUT64(quotient_o,63,0);
    VL_OUT64(remainder_o,63,0);
    
    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    CData/*2:0*/ div_srt4_top__DOT__state_q;
    CData/*2:0*/ div_srt4_top__DOT__state_next;
    CData/*0:0*/ div_srt4_top__DOT__signed_op_q;
    CData/*0:0*/ div_srt4_top__DOT__dividend_sign;
    CData/*0:0*/ div_srt4_top__DOT__divisor_sign;
    CData/*0:0*/ div_srt4_top__DOT__is_overflow;
    CData/*0:0*/ div_srt4_top__DOT__is_a_lt_d;
    CData/*0:0*/ div_srt4_top__DOT__short_circuit;
    CData/*0:0*/ div_srt4_top__DOT__dp_prep_step;
    CData/*0:0*/ div_srt4_top__DOT__dp_iter_step;
    CData/*0:0*/ div_srt4_top__DOT__dp_corr_step;
    CData/*2:0*/ div_srt4_top__DOT__q_digit;
    CData/*0:0*/ div_srt4_top__DOT__div_by_zero_q;
    CData/*0:0*/ div_srt4_top__DOT__div_by_zero_next;
    CData/*0:0*/ div_srt4_top__DOT__overflow_q;
    CData/*0:0*/ div_srt4_top__DOT__overflow_next;
    CData/*0:0*/ div_srt4_top__DOT__valid_o_q;
    CData/*0:0*/ div_srt4_top__DOT__valid_o_next;
    CData/*6:0*/ div_srt4_top__DOT__u_datapath__DOT__lzc_a;
    CData/*6:0*/ div_srt4_top__DOT__u_datapath__DOT__lzc_d;
    CData/*6:0*/ div_srt4_top__DOT__u_datapath__DOT__k_calc;
    CData/*6:0*/ div_srt4_top__DOT__u_datapath__DOT__n_calc;
    CData/*6:0*/ div_srt4_top__DOT__u_datapath__DOT__shift_calc;
    CData/*6:0*/ div_srt4_top__DOT__u_datapath__DOT__n_q;
    CData/*6:0*/ div_srt4_top__DOT__u_datapath__DOT__shift_q;
    CData/*6:0*/ div_srt4_top__DOT__u_datapath__DOT__lzc_d_q;
    CData/*5:0*/ div_srt4_top__DOT__u_datapath__DOT__iter_cnt_q;
    CData/*5:0*/ div_srt4_top__DOT__u_datapath__DOT__iter_cnt_next;
    WData/*67:0*/ div_srt4_top__DOT__u_datapath__DOT__pr_sum_q[3];
    WData/*67:0*/ div_srt4_top__DOT__u_datapath__DOT__pr_carry_q[3];
    WData/*67:0*/ div_srt4_top__DOT__u_datapath__DOT__pr_sum_next[3];
    WData/*67:0*/ div_srt4_top__DOT__u_datapath__DOT__mult[3];
    WData/*67:0*/ div_srt4_top__DOT__u_datapath__DOT__carry_raw[3];
    WData/*67:0*/ div_srt4_top__DOT__u_datapath__DOT__pr_full_q[3];
    WData/*67:0*/ div_srt4_top__DOT__u_datapath__DOT__pr_corrected[3];
    QData/*63:0*/ div_srt4_top__DOT__dividend_q;
    QData/*63:0*/ div_srt4_top__DOT__divisor_q;
    QData/*63:0*/ div_srt4_top__DOT__abs_dividend;
    QData/*63:0*/ div_srt4_top__DOT__abs_divisor;
    QData/*63:0*/ div_srt4_top__DOT__quotient_o_q;
    QData/*63:0*/ div_srt4_top__DOT__quotient_o_next;
    QData/*63:0*/ div_srt4_top__DOT__remainder_o_q;
    QData/*63:0*/ div_srt4_top__DOT__remainder_o_next;
    QData/*63:0*/ div_srt4_top__DOT__u_datapath__DOT__a_norm_calc;
    QData/*63:0*/ div_srt4_top__DOT__u_datapath__DOT__d_norm_calc;
    QData/*63:0*/ div_srt4_top__DOT__u_datapath__DOT__abs_a_q;
    QData/*63:0*/ div_srt4_top__DOT__u_datapath__DOT__abs_d_q;
    QData/*63:0*/ div_srt4_top__DOT__u_datapath__DOT__d_norm_q;
    QData/*63:0*/ div_srt4_top__DOT__u_datapath__DOT__Q_q;
    QData/*63:0*/ div_srt4_top__DOT__u_datapath__DOT__Q_next;
    QData/*63:0*/ div_srt4_top__DOT__u_datapath__DOT__QM_q;
    QData/*63:0*/ div_srt4_top__DOT__u_datapath__DOT__QM_next;
    QData/*63:0*/ div_srt4_top__DOT__u_datapath__DOT__q_corrected;
    
    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    CData/*0:0*/ __Vfunc_div_srt4_top__DOT__apply_sign__0__neg;
    CData/*0:0*/ __Vfunc_div_srt4_top__DOT__apply_sign__1__neg;
    CData/*0:0*/ __Vfunc_div_srt4_top__DOT__apply_sign__2__neg;
    CData/*0:0*/ __Vfunc_div_srt4_top__DOT__apply_sign__3__neg;
    CData/*2:0*/ __Vfunc_qds_lookup__4__Vfuncout;
    CData/*6:0*/ __Vfunc_qds_lookup__4__pr_est;
    CData/*2:0*/ __Vfunc_qds_lookup__4__d_hat;
    CData/*6:0*/ __Vfunc_qds_lookup__4__m2;
    CData/*6:0*/ __Vfunc_qds_lookup__4__m1;
    CData/*6:0*/ __Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout;
    CData/*6:0*/ __Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout;
    CData/*0:0*/ __Vclklast__TOP__clk;
    CData/*0:0*/ __Vclklast__TOP__rst_n;
    QData/*63:0*/ __Vfunc_div_srt4_top__DOT__apply_sign__0__Vfuncout;
    QData/*63:0*/ __Vfunc_div_srt4_top__DOT__apply_sign__0__val;
    QData/*63:0*/ __Vfunc_div_srt4_top__DOT__apply_sign__1__Vfuncout;
    QData/*63:0*/ __Vfunc_div_srt4_top__DOT__apply_sign__1__val;
    QData/*63:0*/ __Vfunc_div_srt4_top__DOT__apply_sign__2__Vfuncout;
    QData/*63:0*/ __Vfunc_div_srt4_top__DOT__apply_sign__2__val;
    QData/*63:0*/ __Vfunc_div_srt4_top__DOT__apply_sign__3__Vfuncout;
    QData/*63:0*/ __Vfunc_div_srt4_top__DOT__apply_sign__3__val;
    QData/*63:0*/ __Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val;
    QData/*63:0*/ __Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val;
    CData/*0:0*/ __Vm_traceActivity[2];
    
    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    Vdiv_srt4_top__Syms* __VlSymsp;  // Symbol table
    
    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vdiv_srt4_top);  ///< Copying not allowed
  public:
    /// Construct the model; called by application code
    /// The special name  may be used to make a wrapper with a
    /// single model invisible with respect to DPI scope names.
    Vdiv_srt4_top(const char* name = "TOP");
    /// Destroy the model; called (often implicitly) by application code
    ~Vdiv_srt4_top();
    /// Trace signals in the model; called by application code
    void trace(VerilatedVcdC* tfp, int levels, int options = 0);
    
    // API METHODS
    /// Evaluate the model.  Application must call when inputs change.
    void eval() { eval_step(); }
    /// Evaluate when calling multiple units/models per time step.
    void eval_step();
    /// Evaluate at end of a timestep for tracing, when using eval_step().
    /// Application must call after all eval() and before time changes.
    void eval_end_step() {}
    /// Simulation complete, run final blocks.  Application must call on completion.
    void final();
    
    // INTERNAL METHODS
  private:
    static void _eval_initial_loop(Vdiv_srt4_top__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(Vdiv_srt4_top__Syms* symsp, bool first);
  private:
    static QData _change_request(Vdiv_srt4_top__Syms* __restrict vlSymsp);
    static QData _change_request_1(Vdiv_srt4_top__Syms* __restrict vlSymsp);
  public:
    static void _combo__TOP__3(Vdiv_srt4_top__Syms* __restrict vlSymsp);
  private:
    void _ctor_var_reset() VL_ATTR_COLD;
  public:
    static void _eval(Vdiv_srt4_top__Syms* __restrict vlSymsp);
  private:
#ifdef VL_DEBUG
    void _eval_debug_assertions();
#endif  // VL_DEBUG
  public:
    static void _eval_initial(Vdiv_srt4_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _eval_settle(Vdiv_srt4_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _sequent__TOP__1(Vdiv_srt4_top__Syms* __restrict vlSymsp);
    static void _settle__TOP__2(Vdiv_srt4_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
  private:
    static void traceChgSub0(void* userp, VerilatedVcd* tracep);
    static void traceChgTop0(void* userp, VerilatedVcd* tracep);
    static void traceCleanup(void* userp, VerilatedVcd* /*unused*/);
    static void traceFullSub0(void* userp, VerilatedVcd* tracep) VL_ATTR_COLD;
    static void traceFullTop0(void* userp, VerilatedVcd* tracep) VL_ATTR_COLD;
    static void traceInitSub0(void* userp, VerilatedVcd* tracep) VL_ATTR_COLD;
    static void traceInitTop(void* userp, VerilatedVcd* tracep) VL_ATTR_COLD;
    void traceRegister(VerilatedVcd* tracep) VL_ATTR_COLD;
    static void traceInit(void* userp, VerilatedVcd* tracep, uint32_t code) VL_ATTR_COLD;
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

//----------


#endif  // guard
