#ifndef EX_MEM_HPP
#define EX_MEM_HPP

#include <systemc.h>
#include "registrador.hpp"
#include "registrador_int.hpp"
#include "flip_flop_d.hpp"

SC_MODULE(ex_mem) {
  sc_in<bool> clk;
  sc_in<bool> earth, vcc;

  sc_in<bool> isJump, regWrite,
    dataRead, dataWrite, memToReg;
  sc_in<sc_uint<2>> flagSel;

  sc_in<bool> ula_zero, ula_negative;
  sc_in<sc_int<32>> ula_result, reg_data;
  sc_in<sc_uint<32>> pc;
  sc_in<sc_uint<26>> absolute;
  sc_in<sc_uint<5>> rd;

  flip_flop_d isJump_reg{"isJump_reg"};
  flip_flop_d regWrite_reg{"regWrite_reg"};
  flip_flop_d dataRead_reg{"dataRead_reg"};
  flip_flop_d dataWrite_reg{"dataWrite_reg"};
  flip_flop_d memToReg_reg{"memToReg_reg"};
  flip_flop_d ula_zero_reg{"ula_zero_reg"};
  flip_flop_d ula_negative_reg{"ula_negative_reg"};

    registrador<2> flagSel_reg{"flagSel_reg"};
    registrador<32> pc_reg{"pc_reg"};
    registrador_int<32> ula_result_reg{"ula_result_reg"};
    registrador_int<32> reg_data_reg{"reg_data_reg"};
    registrador<26> absolute_reg{"absolute_reg"};
    registrador<5> rd_reg{"rd_reg"};


  sc_out<bool> isJump_out, regWrite_out,
    dataRead_out, dataWrite_out, memToReg_out, ula_zero_out, ula_negative_out;
  sc_out<sc_uint<2>> flagSel_out;
  sc_out<sc_uint<5>> rd_out;

  sc_out<sc_uint<32>> pc_out;
  sc_out<sc_int<32>> ula_result_out, reg_data_out;
  sc_out<sc_uint<26>> absolute_out;

  void connect_flip_flop_d(flip_flop_d &ff, sc_in<bool> &in, sc_out<bool> &out);

  template<int N>
  void connect_register(registrador<N> &reg, sc_in<sc_uint<N>> &in, sc_out<sc_uint<N>> &out);

  template<int N>
  void connect_register(registrador_int<N> &reg, sc_in<sc_int<N>> &in, sc_out<sc_int<N>> &out);

  SC_CTOR(ex_mem);
};

#endif
