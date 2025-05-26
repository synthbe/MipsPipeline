#include "../include/mem_wb.hpp"

void mem_wb::connect_flip_flop_d(flip_flop_d &ff, sc_in<bool> &in, sc_out<bool> &out) {
  ff.clk(clk);
  ff.rst(rst);
  ff.a(in);
  ff.b(out);
  ff.we(vcc);
}

template<int N>
void mem_wb::connect_register(registrador<N> &reg, sc_in<sc_uint<N>> &in, sc_out<sc_uint<N>> &out) {
  reg.clk(clk);
  reg.rst(rst);
  reg.we(vcc);
  reg.d_in(in);
  reg.d_out(out);
}

template<int N>
void mem_wb::connect_register(registrador_int<N> &reg, sc_in<sc_int<N>> &in, sc_out<sc_int<N>> &out) {
  reg.clk(clk);
  reg.rst(rst);
  reg.we(vcc);
  reg.d_in(in);
  reg.d_out(out);
}

mem_wb::mem_wb(sc_module_name name) : sc_module(name) {
  connect_flip_flop_d(regWrite_reg, regWrite, regWrite_out);
    connect_flip_flop_d(memToReg_reg, memToReg, memToReg_out);
    connect_register(ula_result_reg, ula_result, ula_result_out);
    connect_register(mem_data_reg, mem_data, mem_data_out);
    connect_register(rd_reg, rd, rd_out);
}
