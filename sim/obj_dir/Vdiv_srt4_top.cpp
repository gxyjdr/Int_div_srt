// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vdiv_srt4_top.h for the primary calling header

#include "Vdiv_srt4_top.h"
#include "Vdiv_srt4_top__Syms.h"

//==========

void Vdiv_srt4_top::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vdiv_srt4_top::eval\n"); );
    Vdiv_srt4_top__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vdiv_srt4_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
#ifdef VL_DEBUG
    // Debug assertions
    _eval_debug_assertions();
#endif  // VL_DEBUG
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Clock loop\n"););
        vlSymsp->__Vm_activity = true;
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("../rtl/div_srt4_top.sv", 13, "",
                "Verilated model didn't converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void Vdiv_srt4_top::_eval_initial_loop(Vdiv_srt4_top__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    _eval_initial(vlSymsp);
    vlSymsp->__Vm_activity = true;
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        _eval_settle(vlSymsp);
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("../rtl/div_srt4_top.sv", 13, "",
                "Verilated model didn't DC converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

VL_INLINE_OPT void Vdiv_srt4_top::_sequent__TOP__1(Vdiv_srt4_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdiv_srt4_top::_sequent__TOP__1\n"); );
    Vdiv_srt4_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    WData/*95:0*/ __Vtemp2[3];
    WData/*95:0*/ __Vtemp5[3];
    WData/*95:0*/ __Vtemp6[3];
    WData/*95:0*/ __Vtemp7[3];
    WData/*95:0*/ __Vtemp15[3];
    WData/*95:0*/ __Vtemp18[3];
    WData/*95:0*/ __Vtemp20[3];
    WData/*95:0*/ __Vtemp27[3];
    WData/*95:0*/ __Vtemp28[3];
    WData/*95:0*/ __Vtemp29[3];
    WData/*95:0*/ __Vtemp32[3];
    WData/*95:0*/ __Vtemp33[3];
    WData/*95:0*/ __Vtemp34[3];
    WData/*95:0*/ __Vtemp44[3];
    WData/*95:0*/ __Vtemp48[3];
    WData/*95:0*/ __Vtemp49[3];
    WData/*95:0*/ __Vtemp52[3];
    WData/*95:0*/ __Vtemp53[3];
    WData/*95:0*/ __Vtemp54[3];
    WData/*95:0*/ __Vtemp55[3];
    WData/*95:0*/ __Vtemp58[3];
    WData/*95:0*/ __Vtemp59[3];
    WData/*95:0*/ __Vtemp63[3];
    WData/*95:0*/ __Vtemp64[3];
    WData/*95:0*/ __Vtemp67[3];
    // Body
    vlTOPp->div_srt4_top__DOT__valid_o_q = ((IData)(vlTOPp->rst_n) 
                                            & (IData)(vlTOPp->div_srt4_top__DOT__valid_o_next));
    vlTOPp->div_srt4_top__DOT__div_by_zero_q = ((IData)(vlTOPp->rst_n) 
                                                & (IData)(vlTOPp->div_srt4_top__DOT__div_by_zero_next));
    vlTOPp->div_srt4_top__DOT__overflow_q = ((IData)(vlTOPp->rst_n) 
                                             & (IData)(vlTOPp->div_srt4_top__DOT__overflow_next));
    if (vlTOPp->rst_n) {
        if (vlTOPp->div_srt4_top__DOT__dp_prep_step) {
            vlTOPp->div_srt4_top__DOT__u_datapath__DOT__iter_cnt_q = 0U;
        } else {
            if (vlTOPp->div_srt4_top__DOT__dp_iter_step) {
                vlTOPp->div_srt4_top__DOT__u_datapath__DOT__iter_cnt_q 
                    = vlTOPp->div_srt4_top__DOT__u_datapath__DOT__iter_cnt_next;
            }
        }
    } else {
        vlTOPp->div_srt4_top__DOT__u_datapath__DOT__iter_cnt_q = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->div_srt4_top__DOT__dp_prep_step) {
            vlTOPp->div_srt4_top__DOT__u_datapath__DOT__n_q 
                = vlTOPp->div_srt4_top__DOT__u_datapath__DOT__n_calc;
        }
    } else {
        vlTOPp->div_srt4_top__DOT__u_datapath__DOT__n_q = 0U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->div_srt4_top__DOT__quotient_o_q = vlTOPp->div_srt4_top__DOT__quotient_o_next;
        vlTOPp->div_srt4_top__DOT__remainder_o_q = vlTOPp->div_srt4_top__DOT__remainder_o_next;
    } else {
        vlTOPp->div_srt4_top__DOT__quotient_o_q = 0ULL;
        vlTOPp->div_srt4_top__DOT__remainder_o_q = 0ULL;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->div_srt4_top__DOT__dp_prep_step) {
            vlTOPp->div_srt4_top__DOT__u_datapath__DOT__lzc_d_q 
                = vlTOPp->div_srt4_top__DOT__u_datapath__DOT__lzc_d;
        }
    } else {
        vlTOPp->div_srt4_top__DOT__u_datapath__DOT__lzc_d_q = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->div_srt4_top__DOT__dp_prep_step) {
            vlTOPp->div_srt4_top__DOT__u_datapath__DOT__shift_q 
                = vlTOPp->div_srt4_top__DOT__u_datapath__DOT__shift_calc;
        }
    } else {
        vlTOPp->div_srt4_top__DOT__u_datapath__DOT__shift_q = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->div_srt4_top__DOT__dp_prep_step) {
            vlTOPp->div_srt4_top__DOT__u_datapath__DOT__QM_q = 0ULL;
        } else {
            if (vlTOPp->div_srt4_top__DOT__dp_iter_step) {
                vlTOPp->div_srt4_top__DOT__u_datapath__DOT__QM_q 
                    = vlTOPp->div_srt4_top__DOT__u_datapath__DOT__QM_next;
            }
        }
    } else {
        vlTOPp->div_srt4_top__DOT__u_datapath__DOT__QM_q = 0ULL;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->div_srt4_top__DOT__dp_prep_step) {
            vlTOPp->div_srt4_top__DOT__u_datapath__DOT__Q_q = 0ULL;
        } else {
            if (vlTOPp->div_srt4_top__DOT__dp_iter_step) {
                vlTOPp->div_srt4_top__DOT__u_datapath__DOT__Q_q 
                    = vlTOPp->div_srt4_top__DOT__u_datapath__DOT__Q_next;
            }
        }
    } else {
        vlTOPp->div_srt4_top__DOT__u_datapath__DOT__Q_q = 0ULL;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->div_srt4_top__DOT__dp_prep_step) {
            vlTOPp->div_srt4_top__DOT__u_datapath__DOT__abs_a_q 
                = vlTOPp->div_srt4_top__DOT__abs_dividend;
        }
    } else {
        vlTOPp->div_srt4_top__DOT__u_datapath__DOT__abs_a_q = 0ULL;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->div_srt4_top__DOT__dp_prep_step) {
            vlTOPp->div_srt4_top__DOT__u_datapath__DOT__abs_d_q 
                = vlTOPp->div_srt4_top__DOT__abs_divisor;
        }
    } else {
        vlTOPp->div_srt4_top__DOT__u_datapath__DOT__abs_d_q = 0ULL;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->div_srt4_top__DOT__dp_prep_step) {
            vlTOPp->div_srt4_top__DOT__u_datapath__DOT__d_norm_q 
                = vlTOPp->div_srt4_top__DOT__u_datapath__DOT__d_norm_calc;
        }
    } else {
        vlTOPp->div_srt4_top__DOT__u_datapath__DOT__d_norm_q = 0ULL;
    }
    if (vlTOPp->rst_n) {
        if ((1U & (~ (IData)(vlTOPp->div_srt4_top__DOT__dp_prep_step)))) {
            if ((1U & (~ (IData)(vlTOPp->div_srt4_top__DOT__dp_iter_step)))) {
                if (vlTOPp->div_srt4_top__DOT__dp_corr_step) {
                    VL_ADD_W(3, __Vtemp2, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_sum_q, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_carry_q);
                    vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_full_q[0U] 
                        = __Vtemp2[0U];
                    vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_full_q[1U] 
                        = __Vtemp2[1U];
                    vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_full_q[2U] 
                        = (0xfU & __Vtemp2[2U]);
                }
            }
        }
    }
    if (vlTOPp->rst_n) {
        if ((((0U == (IData)(vlTOPp->div_srt4_top__DOT__state_q)) 
              & (IData)(vlTOPp->valid_i)) & (IData)(vlTOPp->ready_o))) {
            vlTOPp->div_srt4_top__DOT__dividend_q = vlTOPp->dividend_i;
            vlTOPp->div_srt4_top__DOT__divisor_q = vlTOPp->divisor_i;
            vlTOPp->div_srt4_top__DOT__signed_op_q 
                = vlTOPp->signed_op_i;
        }
    } else {
        vlTOPp->div_srt4_top__DOT__dividend_q = 0ULL;
        vlTOPp->div_srt4_top__DOT__divisor_q = 0ULL;
        vlTOPp->div_srt4_top__DOT__signed_op_q = 0U;
    }
    vlTOPp->valid_o = vlTOPp->div_srt4_top__DOT__valid_o_q;
    vlTOPp->div_by_zero_o = vlTOPp->div_srt4_top__DOT__div_by_zero_q;
    vlTOPp->overflow_o = vlTOPp->div_srt4_top__DOT__overflow_q;
    vlTOPp->div_srt4_top__DOT__u_datapath__DOT__iter_cnt_next 
        = (0x3fU & ((IData)(1U) + (IData)(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__iter_cnt_q)));
    vlTOPp->quotient_o = vlTOPp->div_srt4_top__DOT__quotient_o_q;
    vlTOPp->remainder_o = vlTOPp->div_srt4_top__DOT__remainder_o_q;
    VL_EXTEND_WQ(66,64, __Vtemp5, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__d_norm_q);
    __Vtemp6[0U] = (0xfffffffcU & (__Vtemp5[0U] << 2U));
    __Vtemp6[1U] = ((3U & (__Vtemp5[0U] >> 0x1eU)) 
                    | (0xfffffffcU & (__Vtemp5[1U] 
                                      << 2U)));
    __Vtemp6[2U] = ((3U & (__Vtemp5[1U] >> 0x1eU)) 
                    | (0xfffffffcU & (__Vtemp5[2U] 
                                      << 2U)));
    VL_ADD_W(3, __Vtemp7, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_full_q, __Vtemp6);
    if ((8U & vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_full_q[2U])) {
        vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_corrected[0U] 
            = __Vtemp7[0U];
        vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_corrected[1U] 
            = __Vtemp7[1U];
        vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_corrected[2U] 
            = (0xfU & __Vtemp7[2U]);
        vlTOPp->div_srt4_top__DOT__u_datapath__DOT__q_corrected 
            = vlTOPp->div_srt4_top__DOT__u_datapath__DOT__QM_q;
    } else {
        vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_corrected[0U] 
            = vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_full_q[0U];
        vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_corrected[1U] 
            = vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_full_q[1U];
        vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_corrected[2U] 
            = (0xfU & vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_full_q[2U]);
        vlTOPp->div_srt4_top__DOT__u_datapath__DOT__q_corrected 
            = vlTOPp->div_srt4_top__DOT__u_datapath__DOT__Q_q;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->div_srt4_top__DOT__dp_prep_step) {
            vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_carry_q[0U] = 0U;
            vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_carry_q[1U] = 0U;
            vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_carry_q[2U] = 0U;
        } else {
            if (vlTOPp->div_srt4_top__DOT__dp_iter_step) {
                vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_carry_q[0U] 
                    = (0xfffffffeU & (vlTOPp->div_srt4_top__DOT__u_datapath__DOT__carry_raw[0U] 
                                      << 1U));
                vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_carry_q[1U] 
                    = ((1U & (vlTOPp->div_srt4_top__DOT__u_datapath__DOT__carry_raw[0U] 
                              >> 0x1fU)) | (0xfffffffeU 
                                            & (vlTOPp->div_srt4_top__DOT__u_datapath__DOT__carry_raw[1U] 
                                               << 1U)));
                vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_carry_q[2U] 
                    = ((1U & (vlTOPp->div_srt4_top__DOT__u_datapath__DOT__carry_raw[1U] 
                              >> 0x1fU)) | (0xeU & 
                                            (vlTOPp->div_srt4_top__DOT__u_datapath__DOT__carry_raw[2U] 
                                             << 1U)));
            }
        }
    } else {
        vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_carry_q[0U] = 0U;
        vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_carry_q[1U] = 0U;
        vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_carry_q[2U] = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->div_srt4_top__DOT__dp_prep_step) {
            VL_EXTEND_WQ(68,64, __Vtemp15, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__a_norm_calc);
            vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_sum_q[0U] 
                = __Vtemp15[0U];
            vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_sum_q[1U] 
                = __Vtemp15[1U];
            vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_sum_q[2U] 
                = __Vtemp15[2U];
        } else {
            if (vlTOPp->div_srt4_top__DOT__dp_iter_step) {
                vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_sum_q[0U] 
                    = vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_sum_next[0U];
                vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_sum_q[1U] 
                    = vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_sum_next[1U];
                vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_sum_q[2U] 
                    = vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_sum_next[2U];
            }
        }
    } else {
        vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_sum_q[0U] = 0U;
        vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_sum_q[1U] = 0U;
        vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_sum_q[2U] = 0U;
    }
    vlTOPp->div_srt4_top__DOT__state_q = ((IData)(vlTOPp->rst_n)
                                           ? (IData)(vlTOPp->div_srt4_top__DOT__state_next)
                                           : 0U);
    vlTOPp->div_srt4_top__DOT__is_overflow = (((IData)(vlTOPp->div_srt4_top__DOT__signed_op_q) 
                                               & (0x8000000000000000ULL 
                                                  == vlTOPp->div_srt4_top__DOT__dividend_q)) 
                                              & (0xffffffffffffffffULL 
                                                 == vlTOPp->div_srt4_top__DOT__divisor_q));
    vlTOPp->div_srt4_top__DOT__divisor_sign = ((IData)(vlTOPp->div_srt4_top__DOT__signed_op_q) 
                                               & (IData)(
                                                         (vlTOPp->div_srt4_top__DOT__divisor_q 
                                                          >> 0x3fU)));
    vlTOPp->div_srt4_top__DOT__dividend_sign = ((IData)(vlTOPp->div_srt4_top__DOT__signed_op_q) 
                                                & (IData)(
                                                          (vlTOPp->div_srt4_top__DOT__dividend_q 
                                                           >> 0x3fU)));
    vlTOPp->div_srt4_top__DOT__abs_divisor = ((IData)(vlTOPp->div_srt4_top__DOT__divisor_sign)
                                               ? (- vlTOPp->div_srt4_top__DOT__divisor_q)
                                               : vlTOPp->div_srt4_top__DOT__divisor_q);
    vlTOPp->div_srt4_top__DOT__abs_dividend = ((IData)(vlTOPp->div_srt4_top__DOT__dividend_sign)
                                                ? (- vlTOPp->div_srt4_top__DOT__dividend_q)
                                                : vlTOPp->div_srt4_top__DOT__dividend_q);
    vlTOPp->__Vfunc_qds_lookup__4__d_hat = (7U & (IData)(
                                                         (vlTOPp->div_srt4_top__DOT__u_datapath__DOT__d_norm_q 
                                                          >> 0x3cU)));
    vlTOPp->__Vfunc_qds_lookup__4__pr_est = (0x7fU 
                                             & (((vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_sum_q[2U] 
                                                  << 4U) 
                                                 | (vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_sum_q[1U] 
                                                    >> 0x1cU)) 
                                                + (
                                                   (vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_carry_q[2U] 
                                                    << 4U) 
                                                   | (vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_carry_q[1U] 
                                                      >> 0x1cU))));
    {
        {
            {
                {
                    {
                        if ((4U & (IData)(vlTOPp->__Vfunc_qds_lookup__4__d_hat))) {
                            if ((2U & (IData)(vlTOPp->__Vfunc_qds_lookup__4__d_hat))) {
                                if ((1U & (IData)(vlTOPp->__Vfunc_qds_lookup__4__d_hat))) {
                                    vlTOPp->__Vfunc_qds_lookup__4__m2 = 0x18U;
                                    vlTOPp->__Vfunc_qds_lookup__4__m1 = 8U;
                                } else {
                                    vlTOPp->__Vfunc_qds_lookup__4__m2 = 0x16U;
                                    vlTOPp->__Vfunc_qds_lookup__4__m1 = 8U;
                                }
                            } else {
                                if ((1U & (IData)(vlTOPp->__Vfunc_qds_lookup__4__d_hat))) {
                                    vlTOPp->__Vfunc_qds_lookup__4__m2 = 0x14U;
                                    vlTOPp->__Vfunc_qds_lookup__4__m1 = 6U;
                                } else {
                                    vlTOPp->__Vfunc_qds_lookup__4__m2 = 0x12U;
                                    vlTOPp->__Vfunc_qds_lookup__4__m1 = 6U;
                                }
                            }
                        } else {
                            if ((2U & (IData)(vlTOPp->__Vfunc_qds_lookup__4__d_hat))) {
                                if ((1U & (IData)(vlTOPp->__Vfunc_qds_lookup__4__d_hat))) {
                                    vlTOPp->__Vfunc_qds_lookup__4__m2 = 0x10U;
                                    vlTOPp->__Vfunc_qds_lookup__4__m1 = 4U;
                                } else {
                                    vlTOPp->__Vfunc_qds_lookup__4__m2 = 0x10U;
                                    vlTOPp->__Vfunc_qds_lookup__4__m1 = 4U;
                                }
                            } else {
                                if ((1U & (IData)(vlTOPp->__Vfunc_qds_lookup__4__d_hat))) {
                                    vlTOPp->__Vfunc_qds_lookup__4__m2 = 0xeU;
                                    vlTOPp->__Vfunc_qds_lookup__4__m1 = 4U;
                                } else {
                                    vlTOPp->__Vfunc_qds_lookup__4__m2 = 0xcU;
                                    vlTOPp->__Vfunc_qds_lookup__4__m1 = 4U;
                                }
                            }
                        }
                        if (VL_GTES_III(1,7,7, (IData)(vlTOPp->__Vfunc_qds_lookup__4__pr_est), (IData)(vlTOPp->__Vfunc_qds_lookup__4__m2))) {
                            vlTOPp->__Vfunc_qds_lookup__4__Vfuncout = 2U;
                            goto __Vlabel5;
                        } else {
                            if (VL_GTES_III(1,7,7, (IData)(vlTOPp->__Vfunc_qds_lookup__4__pr_est), (IData)(vlTOPp->__Vfunc_qds_lookup__4__m1))) {
                                vlTOPp->__Vfunc_qds_lookup__4__Vfuncout = 1U;
                                goto __Vlabel4;
                            } else {
                                if (VL_GTES_III(1,7,7, (IData)(vlTOPp->__Vfunc_qds_lookup__4__pr_est), 
                                                (0x7fU 
                                                 & (- (IData)(vlTOPp->__Vfunc_qds_lookup__4__m1))))) {
                                    vlTOPp->__Vfunc_qds_lookup__4__Vfuncout = 0U;
                                    goto __Vlabel3;
                                } else {
                                    if (VL_GTES_III(1,7,7, (IData)(vlTOPp->__Vfunc_qds_lookup__4__pr_est), 
                                                    (0x7fU 
                                                     & (- (IData)(vlTOPp->__Vfunc_qds_lookup__4__m2))))) {
                                        vlTOPp->__Vfunc_qds_lookup__4__Vfuncout = 4U;
                                        goto __Vlabel2;
                                    } else {
                                        vlTOPp->__Vfunc_qds_lookup__4__Vfuncout = 5U;
                                        goto __Vlabel1;
                                    }
                                }
                            }
                        }
                        __Vlabel5: ;
                    }
                    __Vlabel4: ;
                }
                __Vlabel3: ;
            }
            __Vlabel2: ;
        }
        __Vlabel1: ;
    }
    vlTOPp->div_srt4_top__DOT__q_digit = vlTOPp->__Vfunc_qds_lookup__4__Vfuncout;
    vlTOPp->ready_o = 0U;
    if ((1U & (~ ((IData)(vlTOPp->div_srt4_top__DOT__state_q) 
                  >> 2U)))) {
        if ((1U & (~ ((IData)(vlTOPp->div_srt4_top__DOT__state_q) 
                      >> 1U)))) {
            if ((1U & (~ (IData)(vlTOPp->div_srt4_top__DOT__state_q)))) {
                vlTOPp->ready_o = 1U;
            }
        }
    }
    vlTOPp->div_srt4_top__DOT__dp_corr_step = 0U;
    if ((1U & (~ ((IData)(vlTOPp->div_srt4_top__DOT__state_q) 
                  >> 2U)))) {
        if ((2U & (IData)(vlTOPp->div_srt4_top__DOT__state_q))) {
            if ((1U & (IData)(vlTOPp->div_srt4_top__DOT__state_q))) {
                vlTOPp->div_srt4_top__DOT__dp_corr_step = 1U;
            }
        }
    }
    vlTOPp->div_srt4_top__DOT__dp_iter_step = 0U;
    if ((1U & (~ ((IData)(vlTOPp->div_srt4_top__DOT__state_q) 
                  >> 2U)))) {
        if ((2U & (IData)(vlTOPp->div_srt4_top__DOT__state_q))) {
            if ((1U & (~ (IData)(vlTOPp->div_srt4_top__DOT__state_q)))) {
                vlTOPp->div_srt4_top__DOT__dp_iter_step = 1U;
            }
        }
    }
    vlTOPp->busy_o = (0U != (IData)(vlTOPp->div_srt4_top__DOT__state_q));
    vlTOPp->div_srt4_top__DOT__div_by_zero_next = vlTOPp->div_srt4_top__DOT__div_by_zero_q;
    if ((4U & (IData)(vlTOPp->div_srt4_top__DOT__state_q))) {
        if ((1U & (~ ((IData)(vlTOPp->div_srt4_top__DOT__state_q) 
                      >> 1U)))) {
            if ((1U & (~ (IData)(vlTOPp->div_srt4_top__DOT__state_q)))) {
                vlTOPp->div_srt4_top__DOT__div_by_zero_next 
                    = (0ULL == vlTOPp->div_srt4_top__DOT__divisor_q);
            }
        }
    }
    vlTOPp->div_srt4_top__DOT__overflow_next = vlTOPp->div_srt4_top__DOT__overflow_q;
    if ((4U & (IData)(vlTOPp->div_srt4_top__DOT__state_q))) {
        if ((1U & (~ ((IData)(vlTOPp->div_srt4_top__DOT__state_q) 
                      >> 1U)))) {
            if ((1U & (~ (IData)(vlTOPp->div_srt4_top__DOT__state_q)))) {
                vlTOPp->div_srt4_top__DOT__overflow_next 
                    = ((0ULL != vlTOPp->div_srt4_top__DOT__divisor_q) 
                       & (IData)(vlTOPp->div_srt4_top__DOT__is_overflow));
            }
        }
    }
    vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
        = vlTOPp->div_srt4_top__DOT__abs_dividend;
    {
        {
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0x3fU)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0U;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0x3eU)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 1U;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0x3dU)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 2U;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0x3cU)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 3U;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0x3bU)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 4U;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0x3aU)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 5U;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0x39U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 6U;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0x38U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 7U;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0x37U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 8U;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0x36U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 9U;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0x35U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0xaU;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0x34U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0xbU;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0x33U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0xcU;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0x32U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0xdU;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0x31U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0xeU;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0x30U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0xfU;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0x2fU)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0x10U;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0x2eU)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0x11U;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0x2dU)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0x12U;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0x2cU)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0x13U;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0x2bU)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0x14U;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0x2aU)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0x15U;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0x29U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0x16U;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0x28U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0x17U;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0x27U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0x18U;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0x26U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0x19U;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0x25U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0x1aU;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0x24U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0x1bU;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0x23U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0x1cU;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0x22U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0x1dU;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0x21U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0x1eU;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0x20U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0x1fU;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0x1fU)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0x20U;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0x1eU)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0x21U;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0x1dU)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0x22U;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0x1cU)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0x23U;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0x1bU)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0x24U;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0x1aU)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0x25U;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0x19U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0x26U;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0x18U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0x27U;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0x17U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0x28U;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0x16U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0x29U;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0x15U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0x2aU;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0x14U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0x2bU;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0x13U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0x2cU;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0x12U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0x2dU;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0x11U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0x2eU;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0x10U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0x2fU;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0xfU)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0x30U;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0xeU)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0x31U;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0xdU)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0x32U;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0xcU)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0x33U;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0xbU)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0x34U;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 0xaU)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0x35U;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 9U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0x36U;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 8U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0x37U;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 7U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0x38U;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 6U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0x39U;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 5U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0x3aU;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 4U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0x3bU;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 3U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0x3cU;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 2U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0x3dU;
                goto __Vlabel7;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val 
                               >> 1U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0x3eU;
                goto __Vlabel7;
            }
            if ((1U & (IData)(vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0x3fU;
                goto __Vlabel7;
            }
            vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = 0x40U;
            goto __Vlabel6;
            __Vlabel7: ;
        }
        __Vlabel6: ;
    }
    vlTOPp->div_srt4_top__DOT__u_datapath__DOT__lzc_a 
        = vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout;
    vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
        = vlTOPp->div_srt4_top__DOT__abs_divisor;
    {
        {
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0x3fU)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0U;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0x3eU)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 1U;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0x3dU)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 2U;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0x3cU)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 3U;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0x3bU)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 4U;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0x3aU)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 5U;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0x39U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 6U;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0x38U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 7U;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0x37U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 8U;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0x36U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 9U;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0x35U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0xaU;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0x34U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0xbU;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0x33U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0xcU;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0x32U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0xdU;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0x31U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0xeU;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0x30U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0xfU;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0x2fU)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0x10U;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0x2eU)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0x11U;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0x2dU)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0x12U;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0x2cU)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0x13U;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0x2bU)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0x14U;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0x2aU)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0x15U;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0x29U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0x16U;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0x28U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0x17U;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0x27U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0x18U;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0x26U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0x19U;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0x25U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0x1aU;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0x24U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0x1bU;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0x23U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0x1cU;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0x22U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0x1dU;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0x21U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0x1eU;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0x20U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0x1fU;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0x1fU)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0x20U;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0x1eU)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0x21U;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0x1dU)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0x22U;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0x1cU)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0x23U;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0x1bU)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0x24U;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0x1aU)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0x25U;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0x19U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0x26U;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0x18U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0x27U;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0x17U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0x28U;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0x16U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0x29U;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0x15U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0x2aU;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0x14U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0x2bU;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0x13U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0x2cU;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0x12U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0x2dU;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0x11U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0x2eU;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0x10U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0x2fU;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0xfU)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0x30U;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0xeU)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0x31U;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0xdU)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0x32U;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0xcU)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0x33U;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0xbU)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0x34U;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 0xaU)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0x35U;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 9U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0x36U;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 8U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0x37U;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 7U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0x38U;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 6U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0x39U;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 5U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0x3aU;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 4U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0x3bU;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 3U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0x3cU;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 2U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0x3dU;
                goto __Vlabel9;
            }
            if ((1U & (IData)((vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val 
                               >> 1U)))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0x3eU;
                goto __Vlabel9;
            }
            if ((1U & (IData)(vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val))) {
                vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0x3fU;
                goto __Vlabel9;
            }
            vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = 0x40U;
            goto __Vlabel8;
            __Vlabel9: ;
        }
        __Vlabel8: ;
    }
    vlTOPp->div_srt4_top__DOT__u_datapath__DOT__lzc_d 
        = vlTOPp->__Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout;
    vlTOPp->div_srt4_top__DOT__u_datapath__DOT__k_calc 
        = (0x7fU & ((IData)(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__lzc_d) 
                    - (IData)(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__lzc_a)));
    vlTOPp->div_srt4_top__DOT__u_datapath__DOT__n_calc 
        = (0x3fU & (((IData)(3U) + (IData)(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__k_calc)) 
                    >> 1U));
    vlTOPp->div_srt4_top__DOT__u_datapath__DOT__shift_calc 
        = (0x7fU & ((((IData)(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__n_calc) 
                      << 1U) - (IData)(2U)) - (IData)(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__k_calc)));
    vlTOPp->div_srt4_top__DOT__u_datapath__DOT__a_norm_calc 
        = ((0x3fU >= (IData)(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__lzc_a))
            ? (vlTOPp->div_srt4_top__DOT__abs_dividend 
               << (IData)(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__lzc_a))
            : 0ULL);
    vlTOPp->div_srt4_top__DOT__u_datapath__DOT__d_norm_calc 
        = ((0x3fU >= (IData)(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__lzc_d))
            ? (vlTOPp->div_srt4_top__DOT__abs_divisor 
               << (IData)(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__lzc_d))
            : 0ULL);
    vlTOPp->div_srt4_top__DOT__is_a_lt_d = (vlTOPp->div_srt4_top__DOT__abs_dividend 
                                            < vlTOPp->div_srt4_top__DOT__abs_divisor);
    if ((4U & (IData)(vlTOPp->div_srt4_top__DOT__q_digit))) {
        vlTOPp->div_srt4_top__DOT__u_datapath__DOT__Q_next 
            = ((2U & (IData)(vlTOPp->div_srt4_top__DOT__q_digit))
                ? vlTOPp->div_srt4_top__DOT__u_datapath__DOT__Q_q
                : ((1U & (IData)(vlTOPp->div_srt4_top__DOT__q_digit))
                    ? (2ULL | (0xfffffffffffffffcULL 
                               & (vlTOPp->div_srt4_top__DOT__u_datapath__DOT__QM_q 
                                  << 2U))) : (3ULL 
                                              | (0xfffffffffffffffcULL 
                                                 & (vlTOPp->div_srt4_top__DOT__u_datapath__DOT__QM_q 
                                                    << 2U)))));
        vlTOPp->div_srt4_top__DOT__u_datapath__DOT__QM_next 
            = ((2U & (IData)(vlTOPp->div_srt4_top__DOT__q_digit))
                ? vlTOPp->div_srt4_top__DOT__u_datapath__DOT__QM_q
                : ((1U & (IData)(vlTOPp->div_srt4_top__DOT__q_digit))
                    ? (1ULL | (0xfffffffffffffffcULL 
                               & (vlTOPp->div_srt4_top__DOT__u_datapath__DOT__QM_q 
                                  << 2U))) : (2ULL 
                                              | (0xfffffffffffffffcULL 
                                                 & (vlTOPp->div_srt4_top__DOT__u_datapath__DOT__QM_q 
                                                    << 2U)))));
    } else {
        vlTOPp->div_srt4_top__DOT__u_datapath__DOT__Q_next 
            = ((2U & (IData)(vlTOPp->div_srt4_top__DOT__q_digit))
                ? ((1U & (IData)(vlTOPp->div_srt4_top__DOT__q_digit))
                    ? vlTOPp->div_srt4_top__DOT__u_datapath__DOT__Q_q
                    : (2ULL | (0xfffffffffffffffcULL 
                               & (vlTOPp->div_srt4_top__DOT__u_datapath__DOT__Q_q 
                                  << 2U)))) : ((1U 
                                                & (IData)(vlTOPp->div_srt4_top__DOT__q_digit))
                                                ? (1ULL 
                                                   | (0xfffffffffffffffcULL 
                                                      & (vlTOPp->div_srt4_top__DOT__u_datapath__DOT__Q_q 
                                                         << 2U)))
                                                : (0xfffffffffffffffcULL 
                                                   & (vlTOPp->div_srt4_top__DOT__u_datapath__DOT__Q_q 
                                                      << 2U))));
        vlTOPp->div_srt4_top__DOT__u_datapath__DOT__QM_next 
            = ((2U & (IData)(vlTOPp->div_srt4_top__DOT__q_digit))
                ? ((1U & (IData)(vlTOPp->div_srt4_top__DOT__q_digit))
                    ? vlTOPp->div_srt4_top__DOT__u_datapath__DOT__QM_q
                    : (1ULL | (0xfffffffffffffffcULL 
                               & (vlTOPp->div_srt4_top__DOT__u_datapath__DOT__Q_q 
                                  << 2U)))) : ((1U 
                                                & (IData)(vlTOPp->div_srt4_top__DOT__q_digit))
                                                ? (0xfffffffffffffffcULL 
                                                   & (vlTOPp->div_srt4_top__DOT__u_datapath__DOT__Q_q 
                                                      << 2U))
                                                : (3ULL 
                                                   | (0xfffffffffffffffcULL 
                                                      & (vlTOPp->div_srt4_top__DOT__u_datapath__DOT__QM_q 
                                                         << 2U)))));
    }
    VL_EXTEND_WQ(65,64, __Vtemp18, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__d_norm_q);
    VL_EXTEND_WQ(66,64, __Vtemp20, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__d_norm_q);
    VL_EXTEND_WQ(65,64, __Vtemp27, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__d_norm_q);
    __Vtemp28[0U] = (0xfffffff8U & (__Vtemp27[0U] << 3U));
    __Vtemp28[1U] = ((7U & (__Vtemp27[0U] >> 0x1dU)) 
                     | (0xfffffff8U & (__Vtemp27[1U] 
                                       << 3U)));
    __Vtemp28[2U] = ((7U & (__Vtemp27[1U] >> 0x1dU)) 
                     | (0xfffffff8U & (__Vtemp27[2U] 
                                       << 3U)));
    VL_NEGATE_W(3, __Vtemp29, __Vtemp28);
    VL_EXTEND_WQ(66,64, __Vtemp32, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__d_norm_q);
    __Vtemp33[0U] = (0xfffffffcU & (__Vtemp32[0U] << 2U));
    __Vtemp33[1U] = ((3U & (__Vtemp32[0U] >> 0x1eU)) 
                     | (0xfffffffcU & (__Vtemp32[1U] 
                                       << 2U)));
    __Vtemp33[2U] = ((3U & (__Vtemp32[1U] >> 0x1eU)) 
                     | (0xfffffffcU & (__Vtemp32[2U] 
                                       << 2U)));
    VL_NEGATE_W(3, __Vtemp34, __Vtemp33);
    if ((4U & (IData)(vlTOPp->div_srt4_top__DOT__q_digit))) {
        vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[0U] 
            = ((2U & (IData)(vlTOPp->div_srt4_top__DOT__q_digit))
                ? 0U : ((1U & (IData)(vlTOPp->div_srt4_top__DOT__q_digit))
                         ? (0xfffffff8U & (__Vtemp18[0U] 
                                           << 3U)) : 
                        (0xfffffffcU & (__Vtemp20[0U] 
                                        << 2U))));
        vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[1U] 
            = ((2U & (IData)(vlTOPp->div_srt4_top__DOT__q_digit))
                ? 0U : ((1U & (IData)(vlTOPp->div_srt4_top__DOT__q_digit))
                         ? ((7U & (__Vtemp18[0U] >> 0x1dU)) 
                            | (0xfffffff8U & (__Vtemp18[1U] 
                                              << 3U)))
                         : ((3U & (__Vtemp20[0U] >> 0x1eU)) 
                            | (0xfffffffcU & (__Vtemp20[1U] 
                                              << 2U)))));
        vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[2U] 
            = (0xfU & ((2U & (IData)(vlTOPp->div_srt4_top__DOT__q_digit))
                        ? 0U : ((1U & (IData)(vlTOPp->div_srt4_top__DOT__q_digit))
                                 ? ((7U & (__Vtemp18[1U] 
                                           >> 0x1dU)) 
                                    | (0xfffffff8U 
                                       & (__Vtemp18[2U] 
                                          << 3U))) : 
                                ((3U & (__Vtemp20[1U] 
                                        >> 0x1eU)) 
                                 | (0xfffffffcU & (
                                                   __Vtemp20[2U] 
                                                   << 2U))))));
    } else {
        vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[0U] 
            = ((2U & (IData)(vlTOPp->div_srt4_top__DOT__q_digit))
                ? ((1U & (IData)(vlTOPp->div_srt4_top__DOT__q_digit))
                    ? 0U : __Vtemp29[0U]) : ((1U & (IData)(vlTOPp->div_srt4_top__DOT__q_digit))
                                              ? __Vtemp34[0U]
                                              : 0U));
        vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[1U] 
            = ((2U & (IData)(vlTOPp->div_srt4_top__DOT__q_digit))
                ? ((1U & (IData)(vlTOPp->div_srt4_top__DOT__q_digit))
                    ? 0U : __Vtemp29[1U]) : ((1U & (IData)(vlTOPp->div_srt4_top__DOT__q_digit))
                                              ? __Vtemp34[1U]
                                              : 0U));
        vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[2U] 
            = (0xfU & ((2U & (IData)(vlTOPp->div_srt4_top__DOT__q_digit))
                        ? ((1U & (IData)(vlTOPp->div_srt4_top__DOT__q_digit))
                            ? 0U : __Vtemp29[2U]) : 
                       ((1U & (IData)(vlTOPp->div_srt4_top__DOT__q_digit))
                         ? __Vtemp34[2U] : 0U)));
    }
    vlTOPp->div_srt4_top__DOT__quotient_o_next = vlTOPp->div_srt4_top__DOT__quotient_o_q;
    if ((4U & (IData)(vlTOPp->div_srt4_top__DOT__state_q))) {
        if ((1U & (~ ((IData)(vlTOPp->div_srt4_top__DOT__state_q) 
                      >> 1U)))) {
            if ((1U & (~ (IData)(vlTOPp->div_srt4_top__DOT__state_q)))) {
                if ((0ULL == vlTOPp->div_srt4_top__DOT__divisor_q)) {
                    vlTOPp->div_srt4_top__DOT__quotient_o_next = 0xffffffffffffffffULL;
                } else {
                    if (vlTOPp->div_srt4_top__DOT__is_overflow) {
                        vlTOPp->div_srt4_top__DOT__quotient_o_next = 0x8000000000000000ULL;
                    } else {
                        if ((0ULL == vlTOPp->div_srt4_top__DOT__abs_dividend)) {
                            vlTOPp->div_srt4_top__DOT__quotient_o_next = 0ULL;
                        } else {
                            if (vlTOPp->div_srt4_top__DOT__is_a_lt_d) {
                                vlTOPp->div_srt4_top__DOT__quotient_o_next = 0ULL;
                            } else {
                                if ((1ULL == vlTOPp->div_srt4_top__DOT__abs_divisor)) {
                                    vlTOPp->__Vfunc_div_srt4_top__DOT__apply_sign__1__neg 
                                        = ((IData)(vlTOPp->div_srt4_top__DOT__dividend_sign) 
                                           ^ (IData)(vlTOPp->div_srt4_top__DOT__divisor_sign));
                                    vlTOPp->__Vfunc_div_srt4_top__DOT__apply_sign__1__val 
                                        = vlTOPp->div_srt4_top__DOT__abs_dividend;
                                    vlTOPp->__Vfunc_div_srt4_top__DOT__apply_sign__1__Vfuncout 
                                        = ((IData)(vlTOPp->__Vfunc_div_srt4_top__DOT__apply_sign__1__neg)
                                            ? (- vlTOPp->__Vfunc_div_srt4_top__DOT__apply_sign__1__val)
                                            : vlTOPp->__Vfunc_div_srt4_top__DOT__apply_sign__1__val);
                                    vlTOPp->div_srt4_top__DOT__quotient_o_next 
                                        = vlTOPp->__Vfunc_div_srt4_top__DOT__apply_sign__1__Vfuncout;
                                } else {
                                    vlTOPp->__Vfunc_div_srt4_top__DOT__apply_sign__2__neg 
                                        = ((IData)(vlTOPp->div_srt4_top__DOT__dividend_sign) 
                                           ^ (IData)(vlTOPp->div_srt4_top__DOT__divisor_sign));
                                    vlTOPp->__Vfunc_div_srt4_top__DOT__apply_sign__2__val 
                                        = ((0x3fU >= (IData)(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__shift_q))
                                            ? (vlTOPp->div_srt4_top__DOT__u_datapath__DOT__q_corrected 
                                               >> (IData)(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__shift_q))
                                            : 0ULL);
                                    vlTOPp->__Vfunc_div_srt4_top__DOT__apply_sign__2__Vfuncout 
                                        = ((IData)(vlTOPp->__Vfunc_div_srt4_top__DOT__apply_sign__2__neg)
                                            ? (- vlTOPp->__Vfunc_div_srt4_top__DOT__apply_sign__2__val)
                                            : vlTOPp->__Vfunc_div_srt4_top__DOT__apply_sign__2__val);
                                    vlTOPp->div_srt4_top__DOT__quotient_o_next 
                                        = vlTOPp->__Vfunc_div_srt4_top__DOT__apply_sign__2__Vfuncout;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    vlTOPp->div_srt4_top__DOT__remainder_o_next = vlTOPp->div_srt4_top__DOT__remainder_o_q;
    if ((4U & (IData)(vlTOPp->div_srt4_top__DOT__state_q))) {
        if ((1U & (~ ((IData)(vlTOPp->div_srt4_top__DOT__state_q) 
                      >> 1U)))) {
            if ((1U & (~ (IData)(vlTOPp->div_srt4_top__DOT__state_q)))) {
                if ((0ULL == vlTOPp->div_srt4_top__DOT__divisor_q)) {
                    vlTOPp->div_srt4_top__DOT__remainder_o_next 
                        = vlTOPp->div_srt4_top__DOT__dividend_q;
                } else {
                    if (vlTOPp->div_srt4_top__DOT__is_overflow) {
                        vlTOPp->div_srt4_top__DOT__remainder_o_next = 0ULL;
                    } else {
                        if ((0ULL == vlTOPp->div_srt4_top__DOT__abs_dividend)) {
                            vlTOPp->div_srt4_top__DOT__remainder_o_next = 0ULL;
                        } else {
                            if (vlTOPp->div_srt4_top__DOT__is_a_lt_d) {
                                vlTOPp->__Vfunc_div_srt4_top__DOT__apply_sign__0__neg 
                                    = vlTOPp->div_srt4_top__DOT__dividend_sign;
                                vlTOPp->__Vfunc_div_srt4_top__DOT__apply_sign__0__val 
                                    = vlTOPp->div_srt4_top__DOT__abs_dividend;
                                vlTOPp->__Vfunc_div_srt4_top__DOT__apply_sign__0__Vfuncout 
                                    = ((IData)(vlTOPp->__Vfunc_div_srt4_top__DOT__apply_sign__0__neg)
                                        ? (- vlTOPp->__Vfunc_div_srt4_top__DOT__apply_sign__0__val)
                                        : vlTOPp->__Vfunc_div_srt4_top__DOT__apply_sign__0__val);
                                vlTOPp->div_srt4_top__DOT__remainder_o_next 
                                    = vlTOPp->__Vfunc_div_srt4_top__DOT__apply_sign__0__Vfuncout;
                            } else {
                                if ((1ULL == vlTOPp->div_srt4_top__DOT__abs_divisor)) {
                                    vlTOPp->div_srt4_top__DOT__remainder_o_next = 0ULL;
                                } else {
                                    vlTOPp->__Vfunc_div_srt4_top__DOT__apply_sign__3__neg 
                                        = vlTOPp->div_srt4_top__DOT__dividend_sign;
                                    VL_SHIFTR_WWI(68,68,7, __Vtemp44, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_corrected, 
                                                  (0x7fU 
                                                   & ((IData)(2U) 
                                                      + (IData)(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__lzc_d_q))));
                                    VL_SHIFTR_WWI(68,68,32, __Vtemp48, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_corrected, 2U);
                                    VL_EXTEND_WQ(68,64, __Vtemp49, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__d_norm_q);
                                    if ((1U & (IData)(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__q_corrected))) {
                                        __Vtemp52[0U] 
                                            = __Vtemp49[0U];
                                        __Vtemp52[1U] 
                                            = __Vtemp49[1U];
                                        __Vtemp52[2U] 
                                            = __Vtemp49[2U];
                                    } else {
                                        __Vtemp52[0U] = 0U;
                                        __Vtemp52[1U] = 0U;
                                        __Vtemp52[2U] = 0U;
                                    }
                                    VL_ADD_W(3, __Vtemp53, __Vtemp48, __Vtemp52);
                                    __Vtemp54[0U] = 
                                        __Vtemp53[0U];
                                    __Vtemp54[1U] = 
                                        __Vtemp53[1U];
                                    __Vtemp54[2U] = 
                                        (0xfU & __Vtemp53[2U]);
                                    VL_SHIFTR_WWI(68,68,7, __Vtemp55, __Vtemp54, 
                                                  (0x7fU 
                                                   & ((IData)(1U) 
                                                      + (IData)(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__lzc_d_q))));
                                    vlTOPp->__Vfunc_div_srt4_top__DOT__apply_sign__3__val 
                                        = ((0U == (IData)(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__shift_q))
                                            ? (((QData)((IData)(
                                                                __Vtemp44[1U])) 
                                                << 0x20U) 
                                               | (QData)((IData)(
                                                                 __Vtemp44[0U])))
                                            : (((QData)((IData)(
                                                                __Vtemp55[1U])) 
                                                << 0x20U) 
                                               | (QData)((IData)(
                                                                 __Vtemp55[0U]))));
                                    vlTOPp->__Vfunc_div_srt4_top__DOT__apply_sign__3__Vfuncout 
                                        = ((IData)(vlTOPp->__Vfunc_div_srt4_top__DOT__apply_sign__3__neg)
                                            ? (- vlTOPp->__Vfunc_div_srt4_top__DOT__apply_sign__3__val)
                                            : vlTOPp->__Vfunc_div_srt4_top__DOT__apply_sign__3__val);
                                    vlTOPp->div_srt4_top__DOT__remainder_o_next 
                                        = vlTOPp->__Vfunc_div_srt4_top__DOT__apply_sign__3__Vfuncout;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    vlTOPp->div_srt4_top__DOT__short_circuit = ((((
                                                   (0ULL 
                                                    == vlTOPp->div_srt4_top__DOT__divisor_q) 
                                                   | (IData)(vlTOPp->div_srt4_top__DOT__is_overflow)) 
                                                  | (0ULL 
                                                     == vlTOPp->div_srt4_top__DOT__abs_dividend)) 
                                                 | (IData)(vlTOPp->div_srt4_top__DOT__is_a_lt_d)) 
                                                | (1ULL 
                                                   == vlTOPp->div_srt4_top__DOT__abs_divisor));
    __Vtemp58[0U] = (vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_sum_q[0U] 
                     ^ vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_carry_q[0U]);
    __Vtemp58[1U] = (vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_sum_q[1U] 
                     ^ vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_carry_q[1U]);
    __Vtemp58[2U] = (vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_sum_q[2U] 
                     ^ vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_carry_q[2U]);
    VL_SHIFTL_WWI(68,68,32, __Vtemp59, __Vtemp58, 2U);
    vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_sum_next[0U] 
        = (__Vtemp59[0U] ^ vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[0U]);
    vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_sum_next[1U] 
        = (__Vtemp59[1U] ^ vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[1U]);
    vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_sum_next[2U] 
        = (0xfU & (__Vtemp59[2U] ^ vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[2U]));
    VL_SHIFTL_WWI(68,68,32, __Vtemp63, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_sum_q, 2U);
    VL_SHIFTL_WWI(68,68,32, __Vtemp64, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_carry_q, 2U);
    VL_SHIFTL_WWI(68,68,32, __Vtemp67, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_carry_q, 2U);
    vlTOPp->div_srt4_top__DOT__u_datapath__DOT__carry_raw[0U] 
        = ((__Vtemp63[0U] & (__Vtemp64[0U] | vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[0U])) 
           | (__Vtemp67[0U] & vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[0U]));
    vlTOPp->div_srt4_top__DOT__u_datapath__DOT__carry_raw[1U] 
        = ((__Vtemp63[1U] & (__Vtemp64[1U] | vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[1U])) 
           | (__Vtemp67[1U] & vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[1U]));
    vlTOPp->div_srt4_top__DOT__u_datapath__DOT__carry_raw[2U] 
        = (0xfU & ((__Vtemp63[2U] & (__Vtemp64[2U] 
                                     | vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[2U])) 
                   | (__Vtemp67[2U] & vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[2U])));
    vlTOPp->div_srt4_top__DOT__dp_prep_step = 0U;
    if ((1U & (~ ((IData)(vlTOPp->div_srt4_top__DOT__state_q) 
                  >> 2U)))) {
        if ((1U & (~ ((IData)(vlTOPp->div_srt4_top__DOT__state_q) 
                      >> 1U)))) {
            if ((1U & (IData)(vlTOPp->div_srt4_top__DOT__state_q))) {
                if ((1U & (~ (IData)(vlTOPp->div_srt4_top__DOT__short_circuit)))) {
                    vlTOPp->div_srt4_top__DOT__dp_prep_step = 1U;
                }
            }
        }
    }
}

VL_INLINE_OPT void Vdiv_srt4_top::_combo__TOP__3(Vdiv_srt4_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdiv_srt4_top::_combo__TOP__3\n"); );
    Vdiv_srt4_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->div_srt4_top__DOT__valid_o_next = vlTOPp->div_srt4_top__DOT__valid_o_q;
    if ((4U & (IData)(vlTOPp->div_srt4_top__DOT__state_q))) {
        if ((1U & (~ ((IData)(vlTOPp->div_srt4_top__DOT__state_q) 
                      >> 1U)))) {
            if ((1U & (~ (IData)(vlTOPp->div_srt4_top__DOT__state_q)))) {
                vlTOPp->div_srt4_top__DOT__valid_o_next = 1U;
                if (vlTOPp->ready_i) {
                    vlTOPp->div_srt4_top__DOT__valid_o_next = 0U;
                }
            }
        }
    }
    vlTOPp->div_srt4_top__DOT__state_next = vlTOPp->div_srt4_top__DOT__state_q;
    if ((4U & (IData)(vlTOPp->div_srt4_top__DOT__state_q))) {
        if ((2U & (IData)(vlTOPp->div_srt4_top__DOT__state_q))) {
            vlTOPp->div_srt4_top__DOT__state_next = 0U;
        } else {
            if ((1U & (IData)(vlTOPp->div_srt4_top__DOT__state_q))) {
                vlTOPp->div_srt4_top__DOT__state_next = 4U;
            } else {
                if (vlTOPp->ready_i) {
                    vlTOPp->div_srt4_top__DOT__state_next = 0U;
                }
            }
        }
    } else {
        if ((2U & (IData)(vlTOPp->div_srt4_top__DOT__state_q))) {
            if ((1U & (IData)(vlTOPp->div_srt4_top__DOT__state_q))) {
                vlTOPp->div_srt4_top__DOT__state_next = 5U;
            } else {
                if (((IData)(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__iter_cnt_q) 
                     == (0x3fU & ((IData)(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__n_q) 
                                  - (IData)(1U))))) {
                    vlTOPp->div_srt4_top__DOT__state_next = 3U;
                }
            }
        } else {
            if ((1U & (IData)(vlTOPp->div_srt4_top__DOT__state_q))) {
                vlTOPp->div_srt4_top__DOT__state_next 
                    = ((IData)(vlTOPp->div_srt4_top__DOT__short_circuit)
                        ? 4U : 2U);
            } else {
                if (vlTOPp->valid_i) {
                    vlTOPp->div_srt4_top__DOT__state_next = 1U;
                }
            }
        }
    }
}

void Vdiv_srt4_top::_eval(Vdiv_srt4_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdiv_srt4_top::_eval\n"); );
    Vdiv_srt4_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if ((((IData)(vlTOPp->clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__clk))) 
         | ((~ (IData)(vlTOPp->rst_n)) & (IData)(vlTOPp->__Vclklast__TOP__rst_n)))) {
        vlTOPp->_sequent__TOP__1(vlSymsp);
        vlTOPp->__Vm_traceActivity[1U] = 1U;
    }
    vlTOPp->_combo__TOP__3(vlSymsp);
    // Final
    vlTOPp->__Vclklast__TOP__clk = vlTOPp->clk;
    vlTOPp->__Vclklast__TOP__rst_n = vlTOPp->rst_n;
}

VL_INLINE_OPT QData Vdiv_srt4_top::_change_request(Vdiv_srt4_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdiv_srt4_top::_change_request\n"); );
    Vdiv_srt4_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    return (vlTOPp->_change_request_1(vlSymsp));
}

VL_INLINE_OPT QData Vdiv_srt4_top::_change_request_1(Vdiv_srt4_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdiv_srt4_top::_change_request_1\n"); );
    Vdiv_srt4_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vdiv_srt4_top::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdiv_srt4_top::_eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((rst_n & 0xfeU))) {
        Verilated::overWidthError("rst_n");}
    if (VL_UNLIKELY((valid_i & 0xfeU))) {
        Verilated::overWidthError("valid_i");}
    if (VL_UNLIKELY((signed_op_i & 0xfeU))) {
        Verilated::overWidthError("signed_op_i");}
    if (VL_UNLIKELY((ready_i & 0xfeU))) {
        Verilated::overWidthError("ready_i");}
}
#endif  // VL_DEBUG
