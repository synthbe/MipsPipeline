#include "../include/ex_mem.hpp"

void ex_mem::connect_flip_flop_d(flip_flop_d &ff, sc_in<bool> &in, sc_out<bool> &out) {
  ff.clk(clk);
  ff.rst(earth);
  ff.a(in);
  ff.b(out);
  ff.we(vcc);
}

template<int N>
void ex_mem::connect_register(registrador<N> &reg, sc_in<sc_uint<N>> &in, sc_out<sc_uint<N>> &out) {
  reg.clk(clk);
  reg.rst(earth);
  reg.we(vcc);
  reg.d_in(in);
  reg.d_out(out);
}

template<int N>
void ex_mem::connect_register(registrador_int<N> &reg, sc_in<sc_int<N>> &in, sc_out<sc_int<N>> &out) {
  reg.clk(clk);
  reg.rst(earth);
  reg.we(vcc);
  reg.d_in(in);
  reg.d_out(out);
}

ex_mem::ex_mem(sc_module_name name) : sc_module(name) {
  connect_flip_flop_d(isJump_reg, isJump, isJump_out);
  connect_flip_flop_d(regWrite_reg, regWrite, regWrite_out);
    connect_flip_flop_d(dataRead_reg, dataRead, dataRead_out);
    connect_flip_flop_d(dataWrite_reg, dataWrite, dataWrite_out);
    connect_flip_flop_d(ula_zero_reg, ula_zero, ula_zero_out);
    connect_flip_flop_d(ula_negative_reg, ula_negative, ula_negative_out);
    connect_flip_flop_d(memToReg_reg, memToReg, memToReg_out);
    connect_register(ula_result_reg, ula_result, ula_result_out);
    connect_register(flagSel_reg, flagSel, flagSel_out);
    connect_register(pc_reg, pc, pc_out);
    connect_register(reg_data_reg, reg_data, reg_data_out);
    connect_register(absolute_reg, absolute, absolute_out);
    connect_register(rd_reg, rd, rd_out);
}
