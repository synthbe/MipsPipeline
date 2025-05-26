#ifndef MEM_WB_HPP
#define MEM_WB_HPP

#include <systemc.h>
#include "registrador.hpp"
#include "registrador_int.hpp"
#include "flip_flop_d.hpp"

SC_MODULE(mem_wb) {
  sc_in<bool> clk;
  sc_in<bool> rst;
  sc_in<bool> earth, vcc;


  sc_in<bool> regWrite, memToReg;

  sc_in<sc_int<32>> ula_result, mem_data;
  sc_in<sc_uint<5>> rd;

  flip_flop_d regWrite_reg{"regWrite_reg"};
  flip_flop_d memToReg_reg{"memToReg_reg"};

  registrador_int<32> ula_result_reg{"ula_result_reg"};
  registrador_int<32> mem_data_reg{"mem_data_reg"};
  registrador<5> rd_reg{"rd_reg"};


  sc_out<bool> regWrite_out, memToReg_out;
  sc_out<sc_int<32>> ula_result_out, mem_data_out;
  sc_out<sc_uint<5>> rd_out;

  void connect_flip_flop_d(flip_flop_d &ff, sc_in<bool> &in, sc_out<bool> &out);

  template<int N>
  void connect_register(registrador<N> &reg, sc_in<sc_uint<N>> &in, sc_out<sc_uint<N>> &out);

  template<int N>
  void connect_register(registrador_int<N> &reg, sc_in<sc_int<N>> &in, sc_out<sc_int<N>> &out);

  SC_CTOR(mem_wb);
};

#endif
