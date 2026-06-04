// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vdiv_srt4_top__Syms.h"


//======================

void Vdiv_srt4_top::trace(VerilatedVcdC* tfp, int, int) {
    tfp->spTrace()->addInitCb(&traceInit, __VlSymsp);
    traceRegister(tfp->spTrace());
}

void Vdiv_srt4_top::traceInit(void* userp, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vdiv_srt4_top__Syms* __restrict vlSymsp = static_cast<Vdiv_srt4_top__Syms*>(userp);
    if (!Verilated::calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
                        "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->module(vlSymsp->name());
    tracep->scopeEscape(' ');
    Vdiv_srt4_top::traceInitTop(vlSymsp, tracep);
    tracep->scopeEscape('.');
}

//======================


void Vdiv_srt4_top::traceInitTop(void* userp, VerilatedVcd* tracep) {
    Vdiv_srt4_top__Syms* __restrict vlSymsp = static_cast<Vdiv_srt4_top__Syms*>(userp);
    Vdiv_srt4_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    {
        vlTOPp->traceInitSub0(userp, tracep);
    }
}

void Vdiv_srt4_top::traceInitSub0(void* userp, VerilatedVcd* tracep) {
    Vdiv_srt4_top__Syms* __restrict vlSymsp = static_cast<Vdiv_srt4_top__Syms*>(userp);
    Vdiv_srt4_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    const int c = vlSymsp->__Vm_baseCode;
    if (false && tracep && c) {}  // Prevent unused
    // Body
    {
        tracep->declBit(c+116,"clk", false,-1);
        tracep->declBit(c+117,"rst_n", false,-1);
        tracep->declBit(c+118,"valid_i", false,-1);
        tracep->declBit(c+119,"ready_o", false,-1);
        tracep->declQuad(c+120,"dividend_i", false,-1, 63,0);
        tracep->declQuad(c+122,"divisor_i", false,-1, 63,0);
        tracep->declBit(c+124,"signed_op_i", false,-1);
        tracep->declBit(c+125,"valid_o", false,-1);
        tracep->declBit(c+126,"ready_i", false,-1);
        tracep->declQuad(c+127,"quotient_o", false,-1, 63,0);
        tracep->declQuad(c+129,"remainder_o", false,-1, 63,0);
        tracep->declBit(c+131,"div_by_zero_o", false,-1);
        tracep->declBit(c+132,"overflow_o", false,-1);
        tracep->declBit(c+133,"busy_o", false,-1);
        tracep->declBit(c+116,"div_srt4_top clk", false,-1);
        tracep->declBit(c+117,"div_srt4_top rst_n", false,-1);
        tracep->declBit(c+118,"div_srt4_top valid_i", false,-1);
        tracep->declBit(c+119,"div_srt4_top ready_o", false,-1);
        tracep->declQuad(c+120,"div_srt4_top dividend_i", false,-1, 63,0);
        tracep->declQuad(c+122,"div_srt4_top divisor_i", false,-1, 63,0);
        tracep->declBit(c+124,"div_srt4_top signed_op_i", false,-1);
        tracep->declBit(c+125,"div_srt4_top valid_o", false,-1);
        tracep->declBit(c+126,"div_srt4_top ready_i", false,-1);
        tracep->declQuad(c+127,"div_srt4_top quotient_o", false,-1, 63,0);
        tracep->declQuad(c+129,"div_srt4_top remainder_o", false,-1, 63,0);
        tracep->declBit(c+131,"div_srt4_top div_by_zero_o", false,-1);
        tracep->declBit(c+132,"div_srt4_top overflow_o", false,-1);
        tracep->declBit(c+133,"div_srt4_top busy_o", false,-1);
        tracep->declBus(c+1,"div_srt4_top state_q", false,-1, 2,0);
        tracep->declBus(c+134,"div_srt4_top state_next", false,-1, 2,0);
        tracep->declQuad(c+2,"div_srt4_top dividend_q", false,-1, 63,0);
        tracep->declQuad(c+4,"div_srt4_top divisor_q", false,-1, 63,0);
        tracep->declBit(c+6,"div_srt4_top signed_op_q", false,-1);
        tracep->declBit(c+7,"div_srt4_top dividend_sign", false,-1);
        tracep->declBit(c+8,"div_srt4_top divisor_sign", false,-1);
        tracep->declQuad(c+9,"div_srt4_top abs_dividend", false,-1, 63,0);
        tracep->declQuad(c+11,"div_srt4_top abs_divisor", false,-1, 63,0);
        tracep->declBit(c+13,"div_srt4_top is_div_zero", false,-1);
        tracep->declBit(c+14,"div_srt4_top is_overflow", false,-1);
        tracep->declBit(c+15,"div_srt4_top is_a_zero", false,-1);
        tracep->declBit(c+16,"div_srt4_top is_a_lt_d", false,-1);
        tracep->declBit(c+17,"div_srt4_top is_d_one", false,-1);
        tracep->declBit(c+18,"div_srt4_top short_circuit", false,-1);
        tracep->declBit(c+19,"div_srt4_top dp_prep_step", false,-1);
        tracep->declBit(c+20,"div_srt4_top dp_iter_step", false,-1);
        tracep->declBit(c+21,"div_srt4_top dp_corr_step", false,-1);
        tracep->declBit(c+22,"div_srt4_top dp_done", false,-1);
        tracep->declBus(c+23,"div_srt4_top pr_est", false,-1, 6,0);
        tracep->declBus(c+24,"div_srt4_top d_hat", false,-1, 2,0);
        tracep->declBus(c+25,"div_srt4_top q_digit", false,-1, 2,0);
        tracep->declQuad(c+26,"div_srt4_top q_raw", false,-1, 63,0);
        tracep->declQuad(c+28,"div_srt4_top r_raw", false,-1, 63,0);
        tracep->declQuad(c+30,"div_srt4_top quotient_o_q", false,-1, 63,0);
        tracep->declQuad(c+32,"div_srt4_top quotient_o_next", false,-1, 63,0);
        tracep->declQuad(c+34,"div_srt4_top remainder_o_q", false,-1, 63,0);
        tracep->declQuad(c+36,"div_srt4_top remainder_o_next", false,-1, 63,0);
        tracep->declBit(c+38,"div_srt4_top div_by_zero_q", false,-1);
        tracep->declBit(c+39,"div_srt4_top div_by_zero_next", false,-1);
        tracep->declBit(c+40,"div_srt4_top overflow_q", false,-1);
        tracep->declBit(c+41,"div_srt4_top overflow_next", false,-1);
        tracep->declBit(c+42,"div_srt4_top valid_o_q", false,-1);
        tracep->declBit(c+135,"div_srt4_top valid_o_next", false,-1);
        tracep->declBus(c+23,"div_srt4_top u_qds pr_est_i", false,-1, 6,0);
        tracep->declBus(c+24,"div_srt4_top u_qds d_hat_i", false,-1, 2,0);
        tracep->declBus(c+25,"div_srt4_top u_qds q_digit_o", false,-1, 2,0);
        tracep->declBit(c+116,"div_srt4_top u_datapath clk", false,-1);
        tracep->declBit(c+117,"div_srt4_top u_datapath rst_n", false,-1);
        tracep->declQuad(c+9,"div_srt4_top u_datapath abs_dividend_i", false,-1, 63,0);
        tracep->declQuad(c+11,"div_srt4_top u_datapath abs_divisor_i", false,-1, 63,0);
        tracep->declBit(c+19,"div_srt4_top u_datapath prep_step", false,-1);
        tracep->declBit(c+20,"div_srt4_top u_datapath iter_step", false,-1);
        tracep->declBit(c+21,"div_srt4_top u_datapath corr_step", false,-1);
        tracep->declBit(c+22,"div_srt4_top u_datapath done_o", false,-1);
        tracep->declBus(c+23,"div_srt4_top u_datapath pr_est_o", false,-1, 6,0);
        tracep->declBus(c+24,"div_srt4_top u_datapath d_hat_o", false,-1, 2,0);
        tracep->declBus(c+25,"div_srt4_top u_datapath q_digit_i", false,-1, 2,0);
        tracep->declQuad(c+26,"div_srt4_top u_datapath quotient_o", false,-1, 63,0);
        tracep->declQuad(c+28,"div_srt4_top u_datapath remainder_o", false,-1, 63,0);
        tracep->declBus(c+43,"div_srt4_top u_datapath lzc_a", false,-1, 6,0);
        tracep->declBus(c+44,"div_srt4_top u_datapath lzc_d", false,-1, 6,0);
        tracep->declBus(c+45,"div_srt4_top u_datapath k_calc", false,-1, 6,0);
        tracep->declBus(c+46,"div_srt4_top u_datapath n_calc", false,-1, 6,0);
        tracep->declBus(c+47,"div_srt4_top u_datapath shift_calc", false,-1, 6,0);
        tracep->declQuad(c+48,"div_srt4_top u_datapath a_norm_calc", false,-1, 63,0);
        tracep->declQuad(c+50,"div_srt4_top u_datapath d_norm_calc", false,-1, 63,0);
        tracep->declQuad(c+52,"div_srt4_top u_datapath abs_a_q", false,-1, 63,0);
        tracep->declQuad(c+54,"div_srt4_top u_datapath abs_d_q", false,-1, 63,0);
        tracep->declQuad(c+56,"div_srt4_top u_datapath d_norm_q", false,-1, 63,0);
        tracep->declBus(c+58,"div_srt4_top u_datapath n_q", false,-1, 6,0);
        tracep->declBus(c+59,"div_srt4_top u_datapath shift_q", false,-1, 6,0);
        tracep->declBus(c+60,"div_srt4_top u_datapath lzc_d_q", false,-1, 6,0);
        tracep->declArray(c+61,"div_srt4_top u_datapath pr_sum_q", false,-1, 67,0);
        tracep->declArray(c+64,"div_srt4_top u_datapath pr_carry_q", false,-1, 67,0);
        tracep->declArray(c+67,"div_srt4_top u_datapath pr_sum_next", false,-1, 67,0);
        tracep->declArray(c+70,"div_srt4_top u_datapath pr_carry_next", false,-1, 67,0);
        tracep->declQuad(c+73,"div_srt4_top u_datapath Q_q", false,-1, 63,0);
        tracep->declQuad(c+75,"div_srt4_top u_datapath Q_next", false,-1, 63,0);
        tracep->declQuad(c+77,"div_srt4_top u_datapath QM_q", false,-1, 63,0);
        tracep->declQuad(c+79,"div_srt4_top u_datapath QM_next", false,-1, 63,0);
        tracep->declBus(c+81,"div_srt4_top u_datapath iter_cnt_q", false,-1, 5,0);
        tracep->declBus(c+82,"div_srt4_top u_datapath iter_cnt_next", false,-1, 5,0);
        tracep->declArray(c+83,"div_srt4_top u_datapath d_pos_1x", false,-1, 67,0);
        tracep->declArray(c+86,"div_srt4_top u_datapath d_pos_2x", false,-1, 67,0);
        tracep->declArray(c+89,"div_srt4_top u_datapath d_neg_1x", false,-1, 67,0);
        tracep->declArray(c+92,"div_srt4_top u_datapath d_neg_2x", false,-1, 67,0);
        tracep->declArray(c+95,"div_srt4_top u_datapath mult", false,-1, 67,0);
        tracep->declArray(c+98,"div_srt4_top u_datapath pr_4x_sum", false,-1, 67,0);
        tracep->declArray(c+101,"div_srt4_top u_datapath pr_4x_carry", false,-1, 67,0);
        tracep->declArray(c+104,"div_srt4_top u_datapath carry_raw", false,-1, 67,0);
        tracep->declArray(c+107,"div_srt4_top u_datapath pr_full_q", false,-1, 67,0);
        tracep->declBit(c+110,"div_srt4_top u_datapath pr_negative", false,-1);
        tracep->declArray(c+111,"div_srt4_top u_datapath pr_corrected", false,-1, 67,0);
        tracep->declQuad(c+114,"div_srt4_top u_datapath q_corrected", false,-1, 63,0);
        tracep->declQuad(c+26,"div_srt4_top u_datapath q_int", false,-1, 63,0);
        tracep->declQuad(c+28,"div_srt4_top u_datapath r_calc", false,-1, 63,0);
        tracep->declBus(c+136,"div_srt4_pkg WIDTH", false,-1, 31,0);
        tracep->declBus(c+137,"div_srt4_pkg PR_WIDTH", false,-1, 31,0);
        tracep->declBus(c+136,"div_srt4_pkg Q_WIDTH", false,-1, 31,0);
        tracep->declBus(c+138,"div_srt4_pkg QDS_PR_BITS", false,-1, 31,0);
        tracep->declBus(c+139,"div_srt4_pkg QDS_DIV_BITS", false,-1, 31,0);
        tracep->declBus(c+138,"div_srt4_pkg LZC_BITS", false,-1, 31,0);
        tracep->declBus(c+140,"div_srt4_pkg MAX_ITER", false,-1, 31,0);
        tracep->declBus(c+141,"div_srt4_pkg ITER_CNT_BITS", false,-1, 31,0);
    }
}

void Vdiv_srt4_top::traceRegister(VerilatedVcd* tracep) {
    // Body
    {
        tracep->addFullCb(&traceFullTop0, __VlSymsp);
        tracep->addChgCb(&traceChgTop0, __VlSymsp);
        tracep->addCleanupCb(&traceCleanup, __VlSymsp);
    }
}

void Vdiv_srt4_top::traceFullTop0(void* userp, VerilatedVcd* tracep) {
    Vdiv_srt4_top__Syms* __restrict vlSymsp = static_cast<Vdiv_srt4_top__Syms*>(userp);
    Vdiv_srt4_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    {
        vlTOPp->traceFullSub0(userp, tracep);
    }
}

void Vdiv_srt4_top::traceFullSub0(void* userp, VerilatedVcd* tracep) {
    Vdiv_srt4_top__Syms* __restrict vlSymsp = static_cast<Vdiv_srt4_top__Syms*>(userp);
    Vdiv_srt4_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    vluint32_t* const oldp = tracep->oldp(vlSymsp->__Vm_baseCode);
    if (false && oldp) {}  // Prevent unused
    // Variables
    WData/*95:0*/ __Vtemp134[3];
    WData/*95:0*/ __Vtemp138[3];
    WData/*95:0*/ __Vtemp139[3];
    WData/*95:0*/ __Vtemp142[3];
    WData/*95:0*/ __Vtemp143[3];
    WData/*95:0*/ __Vtemp144[3];
    WData/*95:0*/ __Vtemp145[3];
    WData/*95:0*/ __Vtemp148[3];
    WData/*95:0*/ __Vtemp149[3];
    WData/*95:0*/ __Vtemp151[3];
    WData/*95:0*/ __Vtemp154[3];
    WData/*95:0*/ __Vtemp158[3];
    WData/*95:0*/ __Vtemp165[3];
    WData/*95:0*/ __Vtemp172[3];
    WData/*95:0*/ __Vtemp173[3];
    WData/*95:0*/ __Vtemp174[3];
    WData/*95:0*/ __Vtemp175[3];
    WData/*95:0*/ __Vtemp176[3];
    WData/*95:0*/ __Vtemp178[3];
    WData/*95:0*/ __Vtemp179[3];
    WData/*95:0*/ __Vtemp180[3];
    WData/*95:0*/ __Vtemp181[3];
    WData/*95:0*/ __Vtemp183[3];
    WData/*95:0*/ __Vtemp184[3];
    WData/*95:0*/ __Vtemp185[3];
    WData/*95:0*/ __Vtemp186[3];
    WData/*95:0*/ __Vtemp188[3];
    WData/*95:0*/ __Vtemp189[3];
    WData/*95:0*/ __Vtemp191[3];
    WData/*95:0*/ __Vtemp192[3];
    WData/*95:0*/ __Vtemp194[3];
    WData/*95:0*/ __Vtemp195[3];
    WData/*95:0*/ __Vtemp198[3];
    WData/*95:0*/ __Vtemp201[3];
    // Body
    {
        tracep->fullCData(oldp+1,(vlTOPp->div_srt4_top__DOT__state_q),3);
        tracep->fullQData(oldp+2,(vlTOPp->div_srt4_top__DOT__dividend_q),64);
        tracep->fullQData(oldp+4,(vlTOPp->div_srt4_top__DOT__divisor_q),64);
        tracep->fullBit(oldp+6,(vlTOPp->div_srt4_top__DOT__signed_op_q));
        tracep->fullBit(oldp+7,(vlTOPp->div_srt4_top__DOT__dividend_sign));
        tracep->fullBit(oldp+8,(vlTOPp->div_srt4_top__DOT__divisor_sign));
        tracep->fullQData(oldp+9,(vlTOPp->div_srt4_top__DOT__abs_dividend),64);
        tracep->fullQData(oldp+11,(vlTOPp->div_srt4_top__DOT__abs_divisor),64);
        tracep->fullBit(oldp+13,((0ULL == vlTOPp->div_srt4_top__DOT__divisor_q)));
        tracep->fullBit(oldp+14,(vlTOPp->div_srt4_top__DOT__is_overflow));
        tracep->fullBit(oldp+15,((0ULL == vlTOPp->div_srt4_top__DOT__abs_dividend)));
        tracep->fullBit(oldp+16,(vlTOPp->div_srt4_top__DOT__is_a_lt_d));
        tracep->fullBit(oldp+17,((1ULL == vlTOPp->div_srt4_top__DOT__abs_divisor)));
        tracep->fullBit(oldp+18,(vlTOPp->div_srt4_top__DOT__short_circuit));
        tracep->fullBit(oldp+19,(vlTOPp->div_srt4_top__DOT__dp_prep_step));
        tracep->fullBit(oldp+20,(vlTOPp->div_srt4_top__DOT__dp_iter_step));
        tracep->fullBit(oldp+21,(vlTOPp->div_srt4_top__DOT__dp_corr_step));
        tracep->fullBit(oldp+22,(((IData)(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__iter_cnt_q) 
                                  == (0x3fU & ((IData)(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__n_q) 
                                               - (IData)(1U))))));
        tracep->fullCData(oldp+23,((0x7fU & (((vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_sum_q[2U] 
                                               << 4U) 
                                              | (vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_sum_q[1U] 
                                                 >> 0x1cU)) 
                                             + ((vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_carry_q[2U] 
                                                 << 4U) 
                                                | (vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_carry_q[1U] 
                                                   >> 0x1cU))))),7);
        tracep->fullCData(oldp+24,((7U & (IData)((vlTOPp->div_srt4_top__DOT__u_datapath__DOT__d_norm_q 
                                                  >> 0x3cU)))),3);
        tracep->fullCData(oldp+25,(vlTOPp->div_srt4_top__DOT__q_digit),3);
        tracep->fullQData(oldp+26,(((0x3fU >= (IData)(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__shift_q))
                                     ? (vlTOPp->div_srt4_top__DOT__u_datapath__DOT__q_corrected 
                                        >> (IData)(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__shift_q))
                                     : 0ULL)),64);
        VL_SHIFTR_WWI(68,68,7, __Vtemp134, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_corrected, 
                      (0x7fU & ((IData)(2U) + (IData)(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__lzc_d_q))));
        VL_SHIFTR_WWI(68,68,32, __Vtemp138, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_corrected, 2U);
        VL_EXTEND_WQ(68,64, __Vtemp139, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__d_norm_q);
        if ((1U & (IData)(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__q_corrected))) {
            __Vtemp142[0U] = __Vtemp139[0U];
            __Vtemp142[1U] = __Vtemp139[1U];
            __Vtemp142[2U] = __Vtemp139[2U];
        } else {
            __Vtemp142[0U] = 0U;
            __Vtemp142[1U] = 0U;
            __Vtemp142[2U] = 0U;
        }
        VL_ADD_W(3, __Vtemp143, __Vtemp138, __Vtemp142);
        __Vtemp144[0U] = __Vtemp143[0U];
        __Vtemp144[1U] = __Vtemp143[1U];
        __Vtemp144[2U] = (0xfU & __Vtemp143[2U]);
        VL_SHIFTR_WWI(68,68,7, __Vtemp145, __Vtemp144, 
                      (0x7fU & ((IData)(1U) + (IData)(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__lzc_d_q))));
        tracep->fullQData(oldp+28,(((0U == (IData)(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__shift_q))
                                     ? (((QData)((IData)(
                                                         __Vtemp134[1U])) 
                                         << 0x20U) 
                                        | (QData)((IData)(
                                                          __Vtemp134[0U])))
                                     : (((QData)((IData)(
                                                         __Vtemp145[1U])) 
                                         << 0x20U) 
                                        | (QData)((IData)(
                                                          __Vtemp145[0U]))))),64);
        tracep->fullQData(oldp+30,(vlTOPp->div_srt4_top__DOT__quotient_o_q),64);
        tracep->fullQData(oldp+32,(vlTOPp->div_srt4_top__DOT__quotient_o_next),64);
        tracep->fullQData(oldp+34,(vlTOPp->div_srt4_top__DOT__remainder_o_q),64);
        tracep->fullQData(oldp+36,(vlTOPp->div_srt4_top__DOT__remainder_o_next),64);
        tracep->fullBit(oldp+38,(vlTOPp->div_srt4_top__DOT__div_by_zero_q));
        tracep->fullBit(oldp+39,(vlTOPp->div_srt4_top__DOT__div_by_zero_next));
        tracep->fullBit(oldp+40,(vlTOPp->div_srt4_top__DOT__overflow_q));
        tracep->fullBit(oldp+41,(vlTOPp->div_srt4_top__DOT__overflow_next));
        tracep->fullBit(oldp+42,(vlTOPp->div_srt4_top__DOT__valid_o_q));
        tracep->fullCData(oldp+43,(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__lzc_a),7);
        tracep->fullCData(oldp+44,(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__lzc_d),7);
        tracep->fullCData(oldp+45,(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__k_calc),7);
        tracep->fullCData(oldp+46,(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__n_calc),7);
        tracep->fullCData(oldp+47,(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__shift_calc),7);
        tracep->fullQData(oldp+48,(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__a_norm_calc),64);
        tracep->fullQData(oldp+50,(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__d_norm_calc),64);
        tracep->fullQData(oldp+52,(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__abs_a_q),64);
        tracep->fullQData(oldp+54,(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__abs_d_q),64);
        tracep->fullQData(oldp+56,(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__d_norm_q),64);
        tracep->fullCData(oldp+58,(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__n_q),7);
        tracep->fullCData(oldp+59,(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__shift_q),7);
        tracep->fullCData(oldp+60,(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__lzc_d_q),7);
        tracep->fullWData(oldp+61,(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_sum_q),68);
        tracep->fullWData(oldp+64,(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_carry_q),68);
        __Vtemp148[0U] = (vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_sum_q[0U] 
                          ^ vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_carry_q[0U]);
        __Vtemp148[1U] = (vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_sum_q[1U] 
                          ^ vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_carry_q[1U]);
        __Vtemp148[2U] = (vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_sum_q[2U] 
                          ^ vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_carry_q[2U]);
        VL_SHIFTL_WWI(68,68,32, __Vtemp149, __Vtemp148, 2U);
        __Vtemp151[0U] = (__Vtemp149[0U] ^ vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[0U]);
        __Vtemp151[1U] = (__Vtemp149[1U] ^ vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[1U]);
        __Vtemp151[2U] = (0xfU & (__Vtemp149[2U] ^ 
                                  vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[2U]));
        tracep->fullWData(oldp+67,(__Vtemp151),68);
        VL_SHIFTL_WWI(68,68,32, __Vtemp154, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_sum_q, 2U);
        VL_SHIFTL_WWI(68,68,32, __Vtemp158, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_carry_q, 2U);
        VL_SHIFTL_WWI(68,68,32, __Vtemp165, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_carry_q, 2U);
        __Vtemp172[0U] = (0xfffffffeU & (((__Vtemp154[0U] 
                                           & (__Vtemp158[0U] 
                                              | vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[0U])) 
                                          | (__Vtemp165[0U] 
                                             & vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[0U])) 
                                         << 1U));
        __Vtemp172[1U] = ((1U & (((__Vtemp154[0U] & 
                                   (__Vtemp158[0U] 
                                    | vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[0U])) 
                                  | (__Vtemp165[0U] 
                                     & vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[0U])) 
                                 >> 0x1fU)) | (0xfffffffeU 
                                               & (((__Vtemp154[1U] 
                                                    & (__Vtemp158[1U] 
                                                       | vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[1U])) 
                                                   | (__Vtemp165[1U] 
                                                      & vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[1U])) 
                                                  << 1U)));
        __Vtemp172[2U] = ((1U & (((__Vtemp154[1U] & 
                                   (__Vtemp158[1U] 
                                    | vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[1U])) 
                                  | (__Vtemp165[1U] 
                                     & vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[1U])) 
                                 >> 0x1fU)) | (0xeU 
                                               & (((__Vtemp154[2U] 
                                                    << 1U) 
                                                   & ((0x1eU 
                                                       & (__Vtemp158[2U] 
                                                          << 1U)) 
                                                      | (vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[2U] 
                                                         << 1U))) 
                                                  | ((__Vtemp165[2U] 
                                                      & vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[2U]) 
                                                     << 1U))));
        tracep->fullWData(oldp+70,(__Vtemp172),68);
        tracep->fullQData(oldp+73,(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__Q_q),64);
        tracep->fullQData(oldp+75,(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__Q_next),64);
        tracep->fullQData(oldp+77,(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__QM_q),64);
        tracep->fullQData(oldp+79,(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__QM_next),64);
        tracep->fullCData(oldp+81,(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__iter_cnt_q),6);
        tracep->fullCData(oldp+82,((0x3fU & ((IData)(1U) 
                                             + (IData)(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__iter_cnt_q)))),6);
        VL_EXTEND_WQ(66,64, __Vtemp173, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__d_norm_q);
        __Vtemp174[0U] = (0xfffffffcU & (__Vtemp173[0U] 
                                         << 2U));
        __Vtemp174[1U] = ((3U & (__Vtemp173[0U] >> 0x1eU)) 
                          | (0xfffffffcU & (__Vtemp173[1U] 
                                            << 2U)));
        __Vtemp174[2U] = ((3U & (__Vtemp173[1U] >> 0x1eU)) 
                          | (0xfffffffcU & (__Vtemp173[2U] 
                                            << 2U)));
        tracep->fullWData(oldp+83,(__Vtemp174),68);
        VL_EXTEND_WQ(65,64, __Vtemp175, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__d_norm_q);
        __Vtemp176[0U] = (0xfffffff8U & (__Vtemp175[0U] 
                                         << 3U));
        __Vtemp176[1U] = ((7U & (__Vtemp175[0U] >> 0x1dU)) 
                          | (0xfffffff8U & (__Vtemp175[1U] 
                                            << 3U)));
        __Vtemp176[2U] = ((7U & (__Vtemp175[1U] >> 0x1dU)) 
                          | (0xfffffff8U & (__Vtemp175[2U] 
                                            << 3U)));
        tracep->fullWData(oldp+86,(__Vtemp176),68);
        VL_EXTEND_WQ(66,64, __Vtemp178, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__d_norm_q);
        __Vtemp179[0U] = (0xfffffffcU & (__Vtemp178[0U] 
                                         << 2U));
        __Vtemp179[1U] = ((3U & (__Vtemp178[0U] >> 0x1eU)) 
                          | (0xfffffffcU & (__Vtemp178[1U] 
                                            << 2U)));
        __Vtemp179[2U] = ((3U & (__Vtemp178[1U] >> 0x1eU)) 
                          | (0xfffffffcU & (__Vtemp178[2U] 
                                            << 2U)));
        VL_NEGATE_W(3, __Vtemp180, __Vtemp179);
        __Vtemp181[0U] = __Vtemp180[0U];
        __Vtemp181[1U] = __Vtemp180[1U];
        __Vtemp181[2U] = (0xfU & __Vtemp180[2U]);
        tracep->fullWData(oldp+89,(__Vtemp181),68);
        VL_EXTEND_WQ(65,64, __Vtemp183, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__d_norm_q);
        __Vtemp184[0U] = (0xfffffff8U & (__Vtemp183[0U] 
                                         << 3U));
        __Vtemp184[1U] = ((7U & (__Vtemp183[0U] >> 0x1dU)) 
                          | (0xfffffff8U & (__Vtemp183[1U] 
                                            << 3U)));
        __Vtemp184[2U] = ((7U & (__Vtemp183[1U] >> 0x1dU)) 
                          | (0xfffffff8U & (__Vtemp183[2U] 
                                            << 3U)));
        VL_NEGATE_W(3, __Vtemp185, __Vtemp184);
        __Vtemp186[0U] = __Vtemp185[0U];
        __Vtemp186[1U] = __Vtemp185[1U];
        __Vtemp186[2U] = (0xfU & __Vtemp185[2U]);
        tracep->fullWData(oldp+92,(__Vtemp186),68);
        tracep->fullWData(oldp+95,(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult),68);
        VL_SHIFTL_WWI(68,68,32, __Vtemp188, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_sum_q, 2U);
        __Vtemp189[0U] = __Vtemp188[0U];
        __Vtemp189[1U] = __Vtemp188[1U];
        __Vtemp189[2U] = (0xfU & __Vtemp188[2U]);
        tracep->fullWData(oldp+98,(__Vtemp189),68);
        VL_SHIFTL_WWI(68,68,32, __Vtemp191, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_carry_q, 2U);
        __Vtemp192[0U] = __Vtemp191[0U];
        __Vtemp192[1U] = __Vtemp191[1U];
        __Vtemp192[2U] = (0xfU & __Vtemp191[2U]);
        tracep->fullWData(oldp+101,(__Vtemp192),68);
        VL_SHIFTL_WWI(68,68,32, __Vtemp194, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_sum_q, 2U);
        VL_SHIFTL_WWI(68,68,32, __Vtemp195, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_carry_q, 2U);
        VL_SHIFTL_WWI(68,68,32, __Vtemp198, vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_carry_q, 2U);
        __Vtemp201[0U] = ((__Vtemp194[0U] & (__Vtemp195[0U] 
                                             | vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[0U])) 
                          | (__Vtemp198[0U] & vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[0U]));
        __Vtemp201[1U] = ((__Vtemp194[1U] & (__Vtemp195[1U] 
                                             | vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[1U])) 
                          | (__Vtemp198[1U] & vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[1U]));
        __Vtemp201[2U] = (0xfU & ((__Vtemp194[2U] & 
                                   (__Vtemp195[2U] 
                                    | vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[2U])) 
                                  | (__Vtemp198[2U] 
                                     & vlTOPp->div_srt4_top__DOT__u_datapath__DOT__mult[2U])));
        tracep->fullWData(oldp+104,(__Vtemp201),68);
        tracep->fullWData(oldp+107,(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_full_q),68);
        tracep->fullBit(oldp+110,((1U & (vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_full_q[2U] 
                                         >> 3U))));
        tracep->fullWData(oldp+111,(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__pr_corrected),68);
        tracep->fullQData(oldp+114,(vlTOPp->div_srt4_top__DOT__u_datapath__DOT__q_corrected),64);
        tracep->fullBit(oldp+116,(vlTOPp->clk));
        tracep->fullBit(oldp+117,(vlTOPp->rst_n));
        tracep->fullBit(oldp+118,(vlTOPp->valid_i));
        tracep->fullBit(oldp+119,(vlTOPp->ready_o));
        tracep->fullQData(oldp+120,(vlTOPp->dividend_i),64);
        tracep->fullQData(oldp+122,(vlTOPp->divisor_i),64);
        tracep->fullBit(oldp+124,(vlTOPp->signed_op_i));
        tracep->fullBit(oldp+125,(vlTOPp->valid_o));
        tracep->fullBit(oldp+126,(vlTOPp->ready_i));
        tracep->fullQData(oldp+127,(vlTOPp->quotient_o),64);
        tracep->fullQData(oldp+129,(vlTOPp->remainder_o),64);
        tracep->fullBit(oldp+131,(vlTOPp->div_by_zero_o));
        tracep->fullBit(oldp+132,(vlTOPp->overflow_o));
        tracep->fullBit(oldp+133,(vlTOPp->busy_o));
        tracep->fullCData(oldp+134,(vlTOPp->div_srt4_top__DOT__state_next),3);
        tracep->fullBit(oldp+135,(vlTOPp->div_srt4_top__DOT__valid_o_next));
        tracep->fullIData(oldp+136,(0x40U),32);
        tracep->fullIData(oldp+137,(0x44U),32);
        tracep->fullIData(oldp+138,(7U),32);
        tracep->fullIData(oldp+139,(3U),32);
        tracep->fullIData(oldp+140,(0x20U),32);
        tracep->fullIData(oldp+141,(6U),32);
    }
}
