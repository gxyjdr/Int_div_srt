// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vdiv_srt4_top__Syms.h"


void Vdiv_srt4_top::traceChgTop0(void* userp, VerilatedVcd* tracep) {
    Vdiv_srt4_top__Syms* __restrict vlSymsp = static_cast<Vdiv_srt4_top__Syms*>(userp);
    Vdiv_srt4_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    {
        vlTOPp->traceChgSub0(userp, tracep);
    }
}

void Vdiv_srt4_top::traceChgSub0(void* userp, VerilatedVcd* tracep) {
    Vdiv_srt4_top__Syms* __restrict vlSymsp = static_cast<Vdiv_srt4_top__Syms*>(userp);
    Vdiv_srt4_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    vluint32_t* const oldp = tracep->oldp(vlSymsp->__Vm_baseCode + 1);
    if (false && oldp) {}  // Prevent unused
    // Variables
    WData/*95:0*/ __Vtemp203[3];
    WData/*95:0*/ __Vtemp207[3];
    WData/*95:0*/ __Vtemp208[3];
    WData/*95:0*/ __Vtemp211[3];
    WData/*95:0*/ __Vtemp212[3];
    WData/*95:0*/ __Vtemp213[3];
    WData/*95:0*/ __Vtemp214[3];
    WData/*95:0*/ __Vtemp217[3];
    WData/*95:0*/ __Vtemp218[3];
    WData/*95:0*/ __Vtemp220[3];
    WData/*95:0*/ __Vtemp223[3];
    WData/*95:0*/ __Vtemp227[3];
    WData/*95:0*/ __Vtemp234[3];
    WData/*95:0*/ __Vtemp241[3];
    WData/*95:0*/ __Vtemp242[3];
    WData/*95:0*/ __Vtemp243[3];
    WData/*95:0*/ __Vtemp244[3];
    WData/*95:0*/ __Vtemp245[3];
    WData/*95:0*/ __Vtemp247[3];
    WData/*95:0*/ __Vtemp248[3];
    WData/*95:0*/ __Vtemp249[3];
    WData/*95:0*/ __Vtemp250[3];
    WData/*95:0*/ __Vtemp252[3];
    WData/*95:0*/ __Vtemp253[3];
    WData/*95:0*/ __Vtemp254[3];
    WData/*95:0*/ __Vtemp255[3];
    WData/*95:0*/ __Vtemp257[3];
    WData/*95:0*/ __Vtemp258[3];
    WData/*95:0*/ __Vtemp260[3];
    WData/*95:0*/ __Vtemp261[3];
    WData/*95:0*/ __Vtemp263[3];
    WData/*95:0*/ __Vtemp264[3];
    WData/*95:0*/ __Vtemp267[3];
    WData/*95:0*/ __Vtemp270[3];
    // Body
    {
        if (VL_UNLIKELY(vlTOPp->__Vm_traceActivity[1U])) {
            tracep->chgCData(oldp+0,(vlTOPp->div_srt4_top__DOT__state_q),3);
            tracep->chgQData(oldp+1,(vlTOPp->div_srt4_top__DOT__dividend_q),64);
            tracep->chgQData(oldp+3,(vlTOPp->div_srt4_top__DOT__divisor_q),64);
            tracep->chgBit(oldp+5,(vlTOPp->div_srt4_top__DOT__signed_op_q));
            tracep->chgBit(oldp+6,(vlTOPp->div_srt4_top__DOT__dividend_sign));
            tracep->chgBit(oldp+7,(vlTOPp->div_srt4_top__DOT__divisor_sign));
            tracep->chgQData(oldp+8,(vlTOPp->div_srt4_top__DOT__abs_dividend),64);
            tracep->chgQData(oldp+10,(vlTOPp->div_srt4_top__DOT__abs_divisor),64);
            tracep->chgBit(oldp+12,((0ULL == vlTOPp->div_srt4_top__DOT__divisor_q)));
            tracep->chgBit(oldp+13,(vlTOPp->div_srt4_top__DOT__is_overflow));
            tracep->chgBit(oldp+14,((0ULL == vlTOPp->div_srt4_top__DOT__abs_dividend)));
            tracep->chgBit(oldp+15,(vlTOPp->div_srt4_top__DOT__is_a_lt_d));
            tracep->chgBit(oldp+16,((1ULL == vlTOPp->div_srt4_top__DOT__abs_divisor)));
            tracep->chgBit(oldp+17,(vlTOPp->div_srt4_top__DOT__short_circuit));
            tracep->chgBit(oldp+18,(vlTOPp->div_srt4_top__DOT__dp_prep_step));
            tracep->chgBit(oldp+19,(vlTOPp->div_srt4_top__DOT__dp_iter_step));
            tracep->chgBit(oldp+20,(vlTOPp->div_srt4_top__DOT__dp_corr_step));
            tracep->chgBit(oldp+21,(((IData)(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__iter_cnt_q) 
                                     == (0x3fU & ((IData)(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__n_q) 
                                                  - (IData)(1U))))));
            tracep->chgCData(oldp+22,((0x7fU & (((vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_sum_q[2U] 
                                                  << 4U) 
                                                 | (vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_sum_q[1U] 
                                                    >> 0x1cU)) 
                                                + (
                                                   (vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_carry_q[2U] 
                                                    << 4U) 
                                                   | (vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_carry_q[1U] 
                                                      >> 0x1cU))))),7);
            tracep->chgCData(oldp+23,((7U & (IData)(
                                                    (vlTOPp->div_srt4_top__DOT__u_datapath__DOT__d_norm_q 
                                                     >> 0x3cU)))),3);
            tracep->chgCData(oldp+24,(vlTOPp->div_srt4_top__DOT__q_digit),3);
            tracep->chgQData(oldp+25,(((0x3fU >= (IData)(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__shift_q))
                                        ? (vlTOPp->div_srt4_top__DOT__u_datapath__DOT__q_corrected 
                                           >> (IData)(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__shift_q))
                                        : 0ULL)),64);
            VL_SHIFTR_WWI(68,68,7, __Vtemp203, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_corrected, 
                          (0x7fU & ((IData)(2U) + (IData)(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__lzc_d_q))));
            VL_SHIFTR_WWI(68,68,32, __Vtemp207, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_corrected, 2U);
            VL_EXTEND_WQ(68,64, __Vtemp208, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__d_norm_q);
            if ((1U & (IData)(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__q_corrected))) {
                __Vtemp211[0U] = __Vtemp208[0U];
                __Vtemp211[1U] = __Vtemp208[1U];
                __Vtemp211[2U] = __Vtemp208[2U];
            } else {
                __Vtemp211[0U] = 0U;
                __Vtemp211[1U] = 0U;
                __Vtemp211[2U] = 0U;
            }
            VL_ADD_W(3, __Vtemp212, __Vtemp207, __Vtemp211);
            __Vtemp213[0U] = __Vtemp212[0U];
            __Vtemp213[1U] = __Vtemp212[1U];
            __Vtemp213[2U] = (0xfU & __Vtemp212[2U]);
            VL_SHIFTR_WWI(68,68,7, __Vtemp214, __Vtemp213, 
                          (0x7fU & ((IData)(1U) + (IData)(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__lzc_d_q))));
            tracep->chgQData(oldp+27,(((0U == (IData)(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__shift_q))
                                        ? (((QData)((IData)(
                                                            __Vtemp203[1U])) 
                                            << 0x20U) 
                                           | (QData)((IData)(
                                                             __Vtemp203[0U])))
                                        : (((QData)((IData)(
                                                            __Vtemp214[1U])) 
                                            << 0x20U) 
                                           | (QData)((IData)(
                                                             __Vtemp214[0U]))))),64);
            tracep->chgQData(oldp+29,(vlTOPp->div_srt4_top__DOT__quotient_o_q),64);
            tracep->chgQData(oldp+31,(vlTOPp->div_srt4_top__DOT__quotient_o_next),64);
            tracep->chgQData(oldp+33,(vlTOPp->div_srt4_top__DOT__remainder_o_q),64);
            tracep->chgQData(oldp+35,(vlTOPp->div_srt4_top__DOT__remainder_o_next),64);
            tracep->chgBit(oldp+37,(vlTOPp->div_srt4_top__DOT__div_by_zero_q));
            tracep->chgBit(oldp+38,(vlTOPp->div_srt4_top__DOT__div_by_zero_next));
            tracep->chgBit(oldp+39,(vlTOPp->div_srt4_top__DOT__overflow_q));
            tracep->chgBit(oldp+40,(vlTOPp->div_srt4_top__DOT__overflow_next));
            tracep->chgBit(oldp+41,(vlTOPp->div_srt4_top__DOT__valid_o_q));
            tracep->chgCData(oldp+42,(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__lzc_a),7);
            tracep->chgCData(oldp+43,(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__lzc_d),7);
            tracep->chgCData(oldp+44,(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__k_calc),7);
            tracep->chgCData(oldp+45,(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__n_calc),7);
            tracep->chgCData(oldp+46,(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__shift_calc),7);
            tracep->chgQData(oldp+47,(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__a_norm_calc),64);
            tracep->chgQData(oldp+49,(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__d_norm_calc),64);
            tracep->chgQData(oldp+51,(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__abs_a_q),64);
            tracep->chgQData(oldp+53,(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__abs_d_q),64);
            tracep->chgQData(oldp+55,(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__d_norm_q),64);
            tracep->chgCData(oldp+57,(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__n_q),7);
            tracep->chgCData(oldp+58,(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__shift_q),7);
            tracep->chgCData(oldp+59,(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__lzc_d_q),7);
            tracep->chgWData(oldp+60,(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_sum_q),68);
            tracep->chgWData(oldp+63,(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_carry_q),68);
            __Vtemp217[0U] = (vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_sum_q[0U] 
                              ^ vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_carry_q[0U]);
            __Vtemp217[1U] = (vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_sum_q[1U] 
                              ^ vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_carry_q[1U]);
            __Vtemp217[2U] = (vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_sum_q[2U] 
                              ^ vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_carry_q[2U]);
            VL_SHIFTL_WWI(68,68,32, __Vtemp218, __Vtemp217, 2U);
            __Vtemp220[0U] = (__Vtemp218[0U] ^ vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[0U]);
            __Vtemp220[1U] = (__Vtemp218[1U] ^ vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[1U]);
            __Vtemp220[2U] = (0xfU & (__Vtemp218[2U] 
                                      ^ vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[2U]));
            tracep->chgWData(oldp+66,(__Vtemp220),68);
            VL_SHIFTL_WWI(68,68,32, __Vtemp223, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_sum_q, 2U);
            VL_SHIFTL_WWI(68,68,32, __Vtemp227, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_carry_q, 2U);
            VL_SHIFTL_WWI(68,68,32, __Vtemp234, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_carry_q, 2U);
            __Vtemp241[0U] = (0xfffffffeU & (((__Vtemp223[0U] 
                                               & (__Vtemp227[0U] 
                                                  | vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[0U])) 
                                              | (__Vtemp234[0U] 
                                                 & vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[0U])) 
                                             << 1U));
            __Vtemp241[1U] = ((1U & (((__Vtemp223[0U] 
                                       & (__Vtemp227[0U] 
                                          | vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[0U])) 
                                      | (__Vtemp234[0U] 
                                         & vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[0U])) 
                                     >> 0x1fU)) | (0xfffffffeU 
                                                   & (((__Vtemp223[1U] 
                                                        & (__Vtemp227[1U] 
                                                           | vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[1U])) 
                                                       | (__Vtemp234[1U] 
                                                          & vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[1U])) 
                                                      << 1U)));
            __Vtemp241[2U] = ((1U & (((__Vtemp223[1U] 
                                       & (__Vtemp227[1U] 
                                          | vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[1U])) 
                                      | (__Vtemp234[1U] 
                                         & vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[1U])) 
                                     >> 0x1fU)) | (0xeU 
                                                   & (((__Vtemp223[2U] 
                                                        << 1U) 
                                                       & ((0x1eU 
                                                           & (__Vtemp227[2U] 
                                                              << 1U)) 
                                                          | (vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[2U] 
                                                             << 1U))) 
                                                      | ((__Vtemp234[2U] 
                                                          & vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[2U]) 
                                                         << 1U))));
            tracep->chgWData(oldp+69,(__Vtemp241),68);
            tracep->chgQData(oldp+72,(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__Q_q),64);
            tracep->chgQData(oldp+74,(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__Q_next),64);
            tracep->chgQData(oldp+76,(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__QM_q),64);
            tracep->chgQData(oldp+78,(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__QM_next),64);
            tracep->chgCData(oldp+80,(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__iter_cnt_q),6);
            tracep->chgCData(oldp+81,((0x3fU & ((IData)(1U) 
                                                + (IData)(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__iter_cnt_q)))),6);
            VL_EXTEND_WQ(66,64, __Vtemp242, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__d_norm_q);
            __Vtemp243[0U] = (0xfffffffcU & (__Vtemp242[0U] 
                                             << 2U));
            __Vtemp243[1U] = ((3U & (__Vtemp242[0U] 
                                     >> 0x1eU)) | (0xfffffffcU 
                                                   & (__Vtemp242[1U] 
                                                      << 2U)));
            __Vtemp243[2U] = ((3U & (__Vtemp242[1U] 
                                     >> 0x1eU)) | (0xfffffffcU 
                                                   & (__Vtemp242[2U] 
                                                      << 2U)));
            tracep->chgWData(oldp+82,(__Vtemp243),68);
            VL_EXTEND_WQ(65,64, __Vtemp244, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__d_norm_q);
            __Vtemp245[0U] = (0xfffffff8U & (__Vtemp244[0U] 
                                             << 3U));
            __Vtemp245[1U] = ((7U & (__Vtemp244[0U] 
                                     >> 0x1dU)) | (0xfffffff8U 
                                                   & (__Vtemp244[1U] 
                                                      << 3U)));
            __Vtemp245[2U] = ((7U & (__Vtemp244[1U] 
                                     >> 0x1dU)) | (0xfffffff8U 
                                                   & (__Vtemp244[2U] 
                                                      << 3U)));
            tracep->chgWData(oldp+85,(__Vtemp245),68);
            VL_EXTEND_WQ(66,64, __Vtemp247, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__d_norm_q);
            __Vtemp248[0U] = (0xfffffffcU & (__Vtemp247[0U] 
                                             << 2U));
            __Vtemp248[1U] = ((3U & (__Vtemp247[0U] 
                                     >> 0x1eU)) | (0xfffffffcU 
                                                   & (__Vtemp247[1U] 
                                                      << 2U)));
            __Vtemp248[2U] = ((3U & (__Vtemp247[1U] 
                                     >> 0x1eU)) | (0xfffffffcU 
                                                   & (__Vtemp247[2U] 
                                                      << 2U)));
            VL_NEGATE_W(3, __Vtemp249, __Vtemp248);
            __Vtemp250[0U] = __Vtemp249[0U];
            __Vtemp250[1U] = __Vtemp249[1U];
            __Vtemp250[2U] = (0xfU & __Vtemp249[2U]);
            tracep->chgWData(oldp+88,(__Vtemp250),68);
            VL_EXTEND_WQ(65,64, __Vtemp252, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__d_norm_q);
            __Vtemp253[0U] = (0xfffffff8U & (__Vtemp252[0U] 
                                             << 3U));
            __Vtemp253[1U] = ((7U & (__Vtemp252[0U] 
                                     >> 0x1dU)) | (0xfffffff8U 
                                                   & (__Vtemp252[1U] 
                                                      << 3U)));
            __Vtemp253[2U] = ((7U & (__Vtemp252[1U] 
                                     >> 0x1dU)) | (0xfffffff8U 
                                                   & (__Vtemp252[2U] 
                                                      << 3U)));
            VL_NEGATE_W(3, __Vtemp254, __Vtemp253);
            __Vtemp255[0U] = __Vtemp254[0U];
            __Vtemp255[1U] = __Vtemp254[1U];
            __Vtemp255[2U] = (0xfU & __Vtemp254[2U]);
            tracep->chgWData(oldp+91,(__Vtemp255),68);
            tracep->chgWData(oldp+94,(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult),68);
            VL_SHIFTL_WWI(68,68,32, __Vtemp257, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_sum_q, 2U);
            __Vtemp258[0U] = __Vtemp257[0U];
            __Vtemp258[1U] = __Vtemp257[1U];
            __Vtemp258[2U] = (0xfU & __Vtemp257[2U]);
            tracep->chgWData(oldp+97,(__Vtemp258),68);
            VL_SHIFTL_WWI(68,68,32, __Vtemp260, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_carry_q, 2U);
            __Vtemp261[0U] = __Vtemp260[0U];
            __Vtemp261[1U] = __Vtemp260[1U];
            __Vtemp261[2U] = (0xfU & __Vtemp260[2U]);
            tracep->chgWData(oldp+100,(__Vtemp261),68);
            VL_SHIFTL_WWI(68,68,32, __Vtemp263, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_sum_q, 2U);
            VL_SHIFTL_WWI(68,68,32, __Vtemp264, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_carry_q, 2U);
            VL_SHIFTL_WWI(68,68,32, __Vtemp267, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_carry_q, 2U);
            __Vtemp270[0U] = ((__Vtemp263[0U] & (__Vtemp264[0U] 
                                                 | vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[0U])) 
                              | (__Vtemp267[0U] & vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[0U]));
            __Vtemp270[1U] = ((__Vtemp263[1U] & (__Vtemp264[1U] 
                                                 | vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[1U])) 
                              | (__Vtemp267[1U] & vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[1U]));
            __Vtemp270[2U] = (0xfU & ((__Vtemp263[2U] 
                                       & (__Vtemp264[2U] 
                                          | vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[2U])) 
                                      | (__Vtemp267[2U] 
                                         & vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[2U])));
            tracep->chgWData(oldp+103,(__Vtemp270),68);
            tracep->chgWData(oldp+106,(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_full_q),68);
            tracep->chgBit(oldp+109,((1U & (vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_full_q[2U] 
                                            >> 3U))));
            tracep->chgWData(oldp+110,(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_corrected),68);
            tracep->chgQData(oldp+113,(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__q_corrected),64);
        }
        tracep->chgBit(oldp+115,(vlTOPp->clk));
        tracep->chgBit(oldp+116,(vlTOPp->rst_n));
        tracep->chgBit(oldp+117,(vlTOPp->valid_i));
        tracep->chgBit(oldp+118,(vlTOPp->ready_o));
        tracep->chgQData(oldp+119,(vlTOPp->dividend_i),64);
        tracep->chgQData(oldp+121,(vlTOPp->divisor_i),64);
        tracep->chgBit(oldp+123,(vlTOPp->signed_op_i));
        tracep->chgBit(oldp+124,(vlTOPp->valid_o));
        tracep->chgBit(oldp+125,(vlTOPp->ready_i));
        tracep->chgQData(oldp+126,(vlTOPp->quotient_o),64);
        tracep->chgQData(oldp+128,(vlTOPp->remainder_o),64);
        tracep->chgBit(oldp+130,(vlTOPp->div_by_zero_o));
        tracep->chgBit(oldp+131,(vlTOPp->overflow_o));
        tracep->chgBit(oldp+132,(vlTOPp->busy_o));
        tracep->chgCData(oldp+133,(vlTOPp->div_srt4_top__DOT__state_next),3);
        tracep->chgBit(oldp+134,(vlTOPp->div_srt4_top__DOT__valid_o_next));
    }
}

void Vdiv_srt4_top::traceCleanup(void* userp, VerilatedVcd* /*unused*/) {
    Vdiv_srt4_top__Syms* __restrict vlSymsp = static_cast<Vdiv_srt4_top__Syms*>(userp);
    Vdiv_srt4_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    {
        vlSymsp->__Vm_activity = false;
        vlTOPp->__Vm_traceActivity[0U] = 0U;
        vlTOPp->__Vm_traceActivity[1U] = 0U;
    }
}
