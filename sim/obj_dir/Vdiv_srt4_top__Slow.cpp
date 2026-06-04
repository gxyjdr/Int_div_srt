// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vdiv_srt4_top.h for the primary calling header

#include "Vdiv_srt4_top.h"
#include "Vdiv_srt4_top__Syms.h"

//==========

VL_CTOR_IMP(Vdiv_srt4_top) {
    Vdiv_srt4_top__Syms* __restrict vlSymsp = __VlSymsp = new Vdiv_srt4_top__Syms(this, name());
    Vdiv_srt4_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void Vdiv_srt4_top::__Vconfigure(Vdiv_srt4_top__Syms* vlSymsp, bool first) {
    if (false && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
    if (false && this->__VlSymsp) {}  // Prevent unused
    Verilated::timeunit(-12);
    Verilated::timeprecision(-12);
}

Vdiv_srt4_top::~Vdiv_srt4_top() {
    VL_DO_CLEAR(delete __VlSymsp, __VlSymsp = NULL);
}

void Vdiv_srt4_top::_settle__TOP__2(Vdiv_srt4_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdiv_srt4_top::_settle__TOP__2\n"); );
    Vdiv_srt4_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    WData/*95:0*/ __Vtemp72[3];
    WData/*95:0*/ __Vtemp73[3];
    WData/*95:0*/ __Vtemp74[3];
    WData/*95:0*/ __Vtemp80[3];
    WData/*95:0*/ __Vtemp82[3];
    WData/*95:0*/ __Vtemp89[3];
    WData/*95:0*/ __Vtemp90[3];
    WData/*95:0*/ __Vtemp91[3];
    WData/*95:0*/ __Vtemp94[3];
    WData/*95:0*/ __Vtemp95[3];
    WData/*95:0*/ __Vtemp96[3];
    WData/*95:0*/ __Vtemp106[3];
    WData/*95:0*/ __Vtemp107[3];
    WData/*95:0*/ __Vtemp111[3];
    WData/*95:0*/ __Vtemp112[3];
    WData/*95:0*/ __Vtemp115[3];
    WData/*95:0*/ __Vtemp120[3];
    WData/*95:0*/ __Vtemp124[3];
    WData/*95:0*/ __Vtemp125[3];
    WData/*95:0*/ __Vtemp128[3];
    WData/*95:0*/ __Vtemp129[3];
    WData/*95:0*/ __Vtemp130[3];
    WData/*95:0*/ __Vtemp131[3];
    // Body
    vlTOPp->valid_o = vlTOPp->div_srt4_top__DOT__valid_o_q;
    vlTOPp->quotient_o = vlTOPp->div_srt4_top__DOT__quotient_o_q;
    vlTOPp->remainder_o = vlTOPp->div_srt4_top__DOT__remainder_o_q;
    vlTOPp->div_by_zero_o = vlTOPp->div_srt4_top__DOT__div_by_zero_q;
    vlTOPp->overflow_o = vlTOPp->div_srt4_top__DOT__overflow_q;
    vlTOPp->div_srt4_top__DOT__u_datapath__DOT__iter_cnt_next 
        = (0x3fU & ((IData)(1U) + (IData)(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__iter_cnt_q)));
    VL_EXTEND_WQ(66,64, __Vtemp72, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__d_norm_q);
    __Vtemp73[0U] = (0xfffffffcU & (__Vtemp72[0U] << 2U));
    __Vtemp73[1U] = ((3U & (__Vtemp72[0U] >> 0x1eU)) 
                     | (0xfffffffcU & (__Vtemp72[1U] 
                                       << 2U)));
    __Vtemp73[2U] = ((3U & (__Vtemp72[1U] >> 0x1eU)) 
                     | (0xfffffffcU & (__Vtemp72[2U] 
                                       << 2U)));
    VL_ADD_W(3, __Vtemp74, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_full_q, __Vtemp73);
    if ((8U & vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_full_q[2U])) {
        vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_corrected[0U] 
            = __Vtemp74[0U];
        vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_corrected[1U] 
            = __Vtemp74[1U];
        vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_corrected[2U] 
            = (0xfU & __Vtemp74[2U]);
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
    vlTOPp->div_srt4_top__DOT__abs_divisor = ((IData)(vlTOPp->div_srt4_top__DOT__divisor_sign)
                                               ? (- vlTOPp->div_srt4_top__DOT__divisor_q)
                                               : vlTOPp->div_srt4_top__DOT__divisor_q);
    vlTOPp->div_srt4_top__DOT__abs_dividend = ((IData)(vlTOPp->div_srt4_top__DOT__dividend_sign)
                                                ? (- vlTOPp->div_srt4_top__DOT__dividend_q)
                                                : vlTOPp->div_srt4_top__DOT__dividend_q);
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
    VL_EXTEND_WQ(65,64, __Vtemp80, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__d_norm_q);
    VL_EXTEND_WQ(66,64, __Vtemp82, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__d_norm_q);
    VL_EXTEND_WQ(65,64, __Vtemp89, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__d_norm_q);
    __Vtemp90[0U] = (0xfffffff8U & (__Vtemp89[0U] << 3U));
    __Vtemp90[1U] = ((7U & (__Vtemp89[0U] >> 0x1dU)) 
                     | (0xfffffff8U & (__Vtemp89[1U] 
                                       << 3U)));
    __Vtemp90[2U] = ((7U & (__Vtemp89[1U] >> 0x1dU)) 
                     | (0xfffffff8U & (__Vtemp89[2U] 
                                       << 3U)));
    VL_NEGATE_W(3, __Vtemp91, __Vtemp90);
    VL_EXTEND_WQ(66,64, __Vtemp94, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__d_norm_q);
    __Vtemp95[0U] = (0xfffffffcU & (__Vtemp94[0U] << 2U));
    __Vtemp95[1U] = ((3U & (__Vtemp94[0U] >> 0x1eU)) 
                     | (0xfffffffcU & (__Vtemp94[1U] 
                                       << 2U)));
    __Vtemp95[2U] = ((3U & (__Vtemp94[1U] >> 0x1eU)) 
                     | (0xfffffffcU & (__Vtemp94[2U] 
                                       << 2U)));
    VL_NEGATE_W(3, __Vtemp96, __Vtemp95);
    if ((4U & (IData)(vlTOPp->div_srt4_top__DOT__q_digit))) {
        vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[0U] 
            = ((2U & (IData)(vlTOPp->div_srt4_top__DOT__q_digit))
                ? 0U : ((1U & (IData)(vlTOPp->div_srt4_top__DOT__q_digit))
                         ? (0xfffffff8U & (__Vtemp80[0U] 
                                           << 3U)) : 
                        (0xfffffffcU & (__Vtemp82[0U] 
                                        << 2U))));
        vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[1U] 
            = ((2U & (IData)(vlTOPp->div_srt4_top__DOT__q_digit))
                ? 0U : ((1U & (IData)(vlTOPp->div_srt4_top__DOT__q_digit))
                         ? ((7U & (__Vtemp80[0U] >> 0x1dU)) 
                            | (0xfffffff8U & (__Vtemp80[1U] 
                                              << 3U)))
                         : ((3U & (__Vtemp82[0U] >> 0x1eU)) 
                            | (0xfffffffcU & (__Vtemp82[1U] 
                                              << 2U)))));
        vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[2U] 
            = (0xfU & ((2U & (IData)(vlTOPp->div_srt4_top__DOT__q_digit))
                        ? 0U : ((1U & (IData)(vlTOPp->div_srt4_top__DOT__q_digit))
                                 ? ((7U & (__Vtemp80[1U] 
                                           >> 0x1dU)) 
                                    | (0xfffffff8U 
                                       & (__Vtemp80[2U] 
                                          << 3U))) : 
                                ((3U & (__Vtemp82[1U] 
                                        >> 0x1eU)) 
                                 | (0xfffffffcU & (
                                                   __Vtemp82[2U] 
                                                   << 2U))))));
    } else {
        vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[0U] 
            = ((2U & (IData)(vlTOPp->div_srt4_top__DOT__q_digit))
                ? ((1U & (IData)(vlTOPp->div_srt4_top__DOT__q_digit))
                    ? 0U : __Vtemp91[0U]) : ((1U & (IData)(vlTOPp->div_srt4_top__DOT__q_digit))
                                              ? __Vtemp96[0U]
                                              : 0U));
        vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[1U] 
            = ((2U & (IData)(vlTOPp->div_srt4_top__DOT__q_digit))
                ? ((1U & (IData)(vlTOPp->div_srt4_top__DOT__q_digit))
                    ? 0U : __Vtemp91[1U]) : ((1U & (IData)(vlTOPp->div_srt4_top__DOT__q_digit))
                                              ? __Vtemp96[1U]
                                              : 0U));
        vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[2U] 
            = (0xfU & ((2U & (IData)(vlTOPp->div_srt4_top__DOT__q_digit))
                        ? ((1U & (IData)(vlTOPp->div_srt4_top__DOT__q_digit))
                            ? 0U : __Vtemp91[2U]) : 
                       ((1U & (IData)(vlTOPp->div_srt4_top__DOT__q_digit))
                         ? __Vtemp96[2U] : 0U)));
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
    __Vtemp106[0U] = (vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_sum_q[0U] 
                      ^ vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_carry_q[0U]);
    __Vtemp106[1U] = (vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_sum_q[1U] 
                      ^ vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_carry_q[1U]);
    __Vtemp106[2U] = (vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_sum_q[2U] 
                      ^ vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_carry_q[2U]);
    VL_SHIFTL_WWI(68,68,32, __Vtemp107, __Vtemp106, 2U);
    vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_sum_next[0U] 
        = (__Vtemp107[0U] ^ vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[0U]);
    vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_sum_next[1U] 
        = (__Vtemp107[1U] ^ vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[1U]);
    vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_sum_next[2U] 
        = (0xfU & (__Vtemp107[2U] ^ vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[2U]));
    VL_SHIFTL_WWI(68,68,32, __Vtemp111, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_sum_q, 2U);
    VL_SHIFTL_WWI(68,68,32, __Vtemp112, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_carry_q, 2U);
    VL_SHIFTL_WWI(68,68,32, __Vtemp115, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_carry_q, 2U);
    vlTOPp->div_srt4_top__DOT__u_datapath__DOT__carry_raw[0U] 
        = ((__Vtemp111[0U] & (__Vtemp112[0U] | vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[0U])) 
           | (__Vtemp115[0U] & vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[0U]));
    vlTOPp->div_srt4_top__DOT__u_datapath__DOT__carry_raw[1U] 
        = ((__Vtemp111[1U] & (__Vtemp112[1U] | vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[1U])) 
           | (__Vtemp115[1U] & vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[1U]));
    vlTOPp->div_srt4_top__DOT__u_datapath__DOT__carry_raw[2U] 
        = (0xfU & ((__Vtemp111[2U] & (__Vtemp112[2U] 
                                      | vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[2U])) 
                   | (__Vtemp115[2U] & vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[2U])));
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
                                    VL_SHIFTR_WWI(68,68,7, __Vtemp120, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_corrected, 
                                                  (0x7fU 
                                                   & ((IData)(2U) 
                                                      + (IData)(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__lzc_d_q))));
                                    VL_SHIFTR_WWI(68,68,32, __Vtemp124, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_corrected, 2U);
                                    VL_EXTEND_WQ(68,64, __Vtemp125, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__d_norm_q);
                                    if ((1U & (IData)(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__q_corrected))) {
                                        __Vtemp128[0U] 
                                            = __Vtemp125[0U];
                                        __Vtemp128[1U] 
                                            = __Vtemp125[1U];
                                        __Vtemp128[2U] 
                                            = __Vtemp125[2U];
                                    } else {
                                        __Vtemp128[0U] = 0U;
                                        __Vtemp128[1U] = 0U;
                                        __Vtemp128[2U] = 0U;
                                    }
                                    VL_ADD_W(3, __Vtemp129, __Vtemp124, __Vtemp128);
                                    __Vtemp130[0U] 
                                        = __Vtemp129[0U];
                                    __Vtemp130[1U] 
                                        = __Vtemp129[1U];
                                    __Vtemp130[2U] 
                                        = (0xfU & __Vtemp129[2U]);
                                    VL_SHIFTR_WWI(68,68,7, __Vtemp131, __Vtemp130, 
                                                  (0x7fU 
                                                   & ((IData)(1U) 
                                                      + (IData)(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__lzc_d_q))));
                                    vlTOPp->__Vfunc_div_srt4_top__DOT__apply_sign__3__val 
                                        = ((0U == (IData)(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__shift_q))
                                            ? (((QData)((IData)(
                                                                __Vtemp120[1U])) 
                                                << 0x20U) 
                                               | (QData)((IData)(
                                                                 __Vtemp120[0U])))
                                            : (((QData)((IData)(
                                                                __Vtemp131[1U])) 
                                                << 0x20U) 
                                               | (QData)((IData)(
                                                                 __Vtemp131[0U]))));
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

void Vdiv_srt4_top::_eval_initial(Vdiv_srt4_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdiv_srt4_top::_eval_initial\n"); );
    Vdiv_srt4_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vclklast__TOP__clk = vlTOPp->clk;
    vlTOPp->__Vclklast__TOP__rst_n = vlTOPp->rst_n;
}

void Vdiv_srt4_top::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdiv_srt4_top::final\n"); );
    // Variables
    Vdiv_srt4_top__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vdiv_srt4_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vdiv_srt4_top::_eval_settle(Vdiv_srt4_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdiv_srt4_top::_eval_settle\n"); );
    Vdiv_srt4_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_settle__TOP__2(vlSymsp);
    vlTOPp->__Vm_traceActivity[1U] = 1U;
    vlTOPp->__Vm_traceActivity[0U] = 1U;
}

void Vdiv_srt4_top::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdiv_srt4_top::_ctor_var_reset\n"); );
    // Body
    clk = VL_RAND_RESET_I(1);
    rst_n = VL_RAND_RESET_I(1);
    valid_i = VL_RAND_RESET_I(1);
    ready_o = VL_RAND_RESET_I(1);
    dividend_i = VL_RAND_RESET_Q(64);
    divisor_i = VL_RAND_RESET_Q(64);
    signed_op_i = VL_RAND_RESET_I(1);
    valid_o = VL_RAND_RESET_I(1);
    ready_i = VL_RAND_RESET_I(1);
    quotient_o = VL_RAND_RESET_Q(64);
    remainder_o = VL_RAND_RESET_Q(64);
    div_by_zero_o = VL_RAND_RESET_I(1);
    overflow_o = VL_RAND_RESET_I(1);
    busy_o = VL_RAND_RESET_I(1);
    div_srt4_top__DOT__state_q = VL_RAND_RESET_I(3);
    div_srt4_top__DOT__state_next = VL_RAND_RESET_I(3);
    div_srt4_top__DOT__dividend_q = VL_RAND_RESET_Q(64);
    div_srt4_top__DOT__divisor_q = VL_RAND_RESET_Q(64);
    div_srt4_top__DOT__signed_op_q = VL_RAND_RESET_I(1);
    div_srt4_top__DOT__dividend_sign = VL_RAND_RESET_I(1);
    div_srt4_top__DOT__divisor_sign = VL_RAND_RESET_I(1);
    div_srt4_top__DOT__abs_dividend = VL_RAND_RESET_Q(64);
    div_srt4_top__DOT__abs_divisor = VL_RAND_RESET_Q(64);
    div_srt4_top__DOT__is_overflow = VL_RAND_RESET_I(1);
    div_srt4_top__DOT__is_a_lt_d = VL_RAND_RESET_I(1);
    div_srt4_top__DOT__short_circuit = VL_RAND_RESET_I(1);
    div_srt4_top__DOT__dp_prep_step = VL_RAND_RESET_I(1);
    div_srt4_top__DOT__dp_iter_step = VL_RAND_RESET_I(1);
    div_srt4_top__DOT__dp_corr_step = VL_RAND_RESET_I(1);
    div_srt4_top__DOT__q_digit = VL_RAND_RESET_I(3);
    div_srt4_top__DOT__quotient_o_q = VL_RAND_RESET_Q(64);
    div_srt4_top__DOT__quotient_o_next = VL_RAND_RESET_Q(64);
    div_srt4_top__DOT__remainder_o_q = VL_RAND_RESET_Q(64);
    div_srt4_top__DOT__remainder_o_next = VL_RAND_RESET_Q(64);
    div_srt4_top__DOT__div_by_zero_q = VL_RAND_RESET_I(1);
    div_srt4_top__DOT__div_by_zero_next = VL_RAND_RESET_I(1);
    div_srt4_top__DOT__overflow_q = VL_RAND_RESET_I(1);
    div_srt4_top__DOT__overflow_next = VL_RAND_RESET_I(1);
    div_srt4_top__DOT__valid_o_q = VL_RAND_RESET_I(1);
    div_srt4_top__DOT__valid_o_next = VL_RAND_RESET_I(1);
    div_srt4_top__DOT__u_datapath__DOT__lzc_a = VL_RAND_RESET_I(7);
    div_srt4_top__DOT__u_datapath__DOT__lzc_d = VL_RAND_RESET_I(7);
    div_srt4_top__DOT__u_datapath__DOT__k_calc = VL_RAND_RESET_I(7);
    div_srt4_top__DOT__u_datapath__DOT__n_calc = VL_RAND_RESET_I(7);
    div_srt4_top__DOT__u_datapath__DOT__shift_calc = VL_RAND_RESET_I(7);
    div_srt4_top__DOT__u_datapath__DOT__a_norm_calc = VL_RAND_RESET_Q(64);
    div_srt4_top__DOT__u_datapath__DOT__d_norm_calc = VL_RAND_RESET_Q(64);
    div_srt4_top__DOT__u_datapath__DOT__abs_a_q = VL_RAND_RESET_Q(64);
    div_srt4_top__DOT__u_datapath__DOT__abs_d_q = VL_RAND_RESET_Q(64);
    div_srt4_top__DOT__u_datapath__DOT__d_norm_q = VL_RAND_RESET_Q(64);
    div_srt4_top__DOT__u_datapath__DOT__n_q = VL_RAND_RESET_I(7);
    div_srt4_top__DOT__u_datapath__DOT__shift_q = VL_RAND_RESET_I(7);
    div_srt4_top__DOT__u_datapath__DOT__lzc_d_q = VL_RAND_RESET_I(7);
    VL_RAND_RESET_W(68, div_srt4_top__DOT__u_datapath__DOT__pr_sum_q);
    VL_RAND_RESET_W(68, div_srt4_top__DOT__u_datapath__DOT__pr_carry_q);
    VL_RAND_RESET_W(68, div_srt4_top__DOT__u_datapath__DOT__pr_sum_next);
    div_srt4_top__DOT__u_datapath__DOT__Q_q = VL_RAND_RESET_Q(64);
    div_srt4_top__DOT__u_datapath__DOT__Q_next = VL_RAND_RESET_Q(64);
    div_srt4_top__DOT__u_datapath__DOT__QM_q = VL_RAND_RESET_Q(64);
    div_srt4_top__DOT__u_datapath__DOT__QM_next = VL_RAND_RESET_Q(64);
    div_srt4_top__DOT__u_datapath__DOT__iter_cnt_q = VL_RAND_RESET_I(6);
    div_srt4_top__DOT__u_datapath__DOT__iter_cnt_next = VL_RAND_RESET_I(6);
    VL_RAND_RESET_W(68, div_srt4_top__DOT__u_datapath__DOT__mult);
    VL_RAND_RESET_W(68, div_srt4_top__DOT__u_datapath__DOT__carry_raw);
    VL_RAND_RESET_W(68, div_srt4_top__DOT__u_datapath__DOT__pr_full_q);
    VL_RAND_RESET_W(68, div_srt4_top__DOT__u_datapath__DOT__pr_corrected);
    div_srt4_top__DOT__u_datapath__DOT__q_corrected = VL_RAND_RESET_Q(64);
    __Vfunc_div_srt4_top__DOT__apply_sign__0__Vfuncout = VL_RAND_RESET_Q(64);
    __Vfunc_div_srt4_top__DOT__apply_sign__0__val = VL_RAND_RESET_Q(64);
    __Vfunc_div_srt4_top__DOT__apply_sign__0__neg = VL_RAND_RESET_I(1);
    __Vfunc_div_srt4_top__DOT__apply_sign__1__Vfuncout = VL_RAND_RESET_Q(64);
    __Vfunc_div_srt4_top__DOT__apply_sign__1__val = VL_RAND_RESET_Q(64);
    __Vfunc_div_srt4_top__DOT__apply_sign__1__neg = VL_RAND_RESET_I(1);
    __Vfunc_div_srt4_top__DOT__apply_sign__2__Vfuncout = VL_RAND_RESET_Q(64);
    __Vfunc_div_srt4_top__DOT__apply_sign__2__val = VL_RAND_RESET_Q(64);
    __Vfunc_div_srt4_top__DOT__apply_sign__2__neg = VL_RAND_RESET_I(1);
    __Vfunc_div_srt4_top__DOT__apply_sign__3__Vfuncout = VL_RAND_RESET_Q(64);
    __Vfunc_div_srt4_top__DOT__apply_sign__3__val = VL_RAND_RESET_Q(64);
    __Vfunc_div_srt4_top__DOT__apply_sign__3__neg = VL_RAND_RESET_I(1);
    __Vfunc_qds_lookup__4__Vfuncout = VL_RAND_RESET_I(3);
    __Vfunc_qds_lookup__4__pr_est = VL_RAND_RESET_I(7);
    __Vfunc_qds_lookup__4__d_hat = VL_RAND_RESET_I(3);
    __Vfunc_qds_lookup__4__m2 = VL_RAND_RESET_I(7);
    __Vfunc_qds_lookup__4__m1 = VL_RAND_RESET_I(7);
    __Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__Vfuncout = VL_RAND_RESET_I(7);
    __Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__5__val = VL_RAND_RESET_Q(64);
    __Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__Vfuncout = VL_RAND_RESET_I(7);
    __Vfunc_div_srt4_top__DOT__u_datapath__DOT__clz64__6__val = VL_RAND_RESET_Q(64);
    { int __Vi0=0; for (; __Vi0<2; ++__Vi0) {
            __Vm_traceActivity[__Vi0] = VL_RAND_RESET_I(1);
    }}
}
