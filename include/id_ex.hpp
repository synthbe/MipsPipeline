#ifndef ID_EX_HPP
#define ID_EX_HPP

#include "registrador.hpp"
#include "flip_flop_d.hpp"
#include <systemc.h>

SC_MODULE(id_ex) {
  sc_in<bool> clk;
  sc_in<bool> rst;
  sc_in<bool> earth, vcc;


  sc_in<bool> isJump, regWrite, op2Sel,
    dataRead, dataWrite, memToReg;
  sc_in<sc_uint<11>> opUla;
  sc_in<sc_uint<2>> flagSel;

  sc_in<sc_int<32>> read1, read2, immediate;
  sc_in<sc_uint<32>> pc;
  sc_in<sc_uint<5>> rd, rt, rs;

  flip_flop_d isJump_reg{"isJump_reg"};
  flip_flop_d regWrite_reg{"regWrite_reg"};
  flip_flop_d op2Sel_reg{"op2Sel_reg"};
  flip_flop_d dataRead_reg{"dataRead_reg"};
  flip_flop_d dataWrite_reg{"dataWrite_reg"};
  flip_flop_d memToReg_reg{"memToReg_reg"};

    registrador<11> opUla_reg{"opUla_reg"};
    registrador<2> flagSel_reg{"flagSel_reg"};
    registrador<32> read1_reg{"read1_reg"};
    registrador<32> read2_reg{"read2_reg"};
    registrador<32> immediate_reg{"immediate_reg"};
    registrador<32> pc_reg{"pc_reg"};
    registrador<5> rd_reg{"rd_reg"};
    registrador<5> rt_reg{"rt_reg"};
    registrador<5> rs_reg{"rs_reg"};


  sc_out<bool> isJump_out, regWrite_out, op2Sel_out,
    dataRead_out, dataWrite_out, memToReg_out;
  sc_out<sc_uint<11>> opUla_out;
  sc_out<sc_uint<2>> flagSel_out;

  sc_out<sc_int<32>> read1_out, read2_out, immediate_out;
  sc_out<sc_uint<32>> pc_out;
  sc_out<sc_uint<5>> rd_out, rt_out, rs_out;

  sc_signal<sc_uint<32>> read1_uint, read2_uint, immediate_uint;
  sc_signal<sc_uint<32>> read1_out_uint, read2_out_uint, immediate_out_uint;

  void connect_flip_flop_d(flip_flop_d &ff, sc_in<bool> &in, sc_out<bool> &out);

  template<int N>
  void connect_register(registrador<N> &reg, sc_in<sc_uint<N>> &in, sc_out<sc_uint<N>> &out);

  template<int N>
  void connect_register(registrador<N> &reg, sc_signal<sc_uint<N>> &in, sc_signal<sc_uint<N>> &out);


  void process();

  SC_CTOR(id_ex);
};

#endif
