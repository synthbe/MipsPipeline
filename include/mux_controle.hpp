#ifndef MUX_CONTROLE_HPP
#define MUX_CONTROLE_HPP

#include <systemc.h>

SC_MODULE(mux_controle) {
  sc_in<bool> sel;

  sc_in<bool> isJump, regWrite, op2Sel,
    dataRead, dataWrite, memToReg;
  sc_in<sc_uint<11>> opUla;
  sc_in<sc_uint<2>> flagSel;

  
  sc_out<bool> isJump_out, regWrite_out, op2Sel_out,
    dataRead_out, dataWrite_out, memToReg_out;
  sc_out<sc_uint<11>> opUla_out;
  sc_out<sc_uint<2>> flagSel_out;

  void process();

  SC_CTOR(mux_controle);
};

#endif