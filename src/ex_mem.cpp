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
void ex_mem::connect_register(registrador<N> &reg, sc_signal<sc_uint<N>> &in, sc_signal<sc_uint<N>> &out) {
  reg.clk(clk);
  reg.rst(earth);
  reg.we(vcc);
  reg.d_in(in);
  reg.d_out(out);
}

void ex_mem::process() {
    ula_result_uint.write(static_cast<sc_uint<32>>(ula_result.read()));
    ula_result_out.write(static_cast<sc_int<32>>(ula_result_out_uint.read()));

    reg_data_uint.write(static_cast<sc_uint<32>>(reg_data.read()));
    reg_data_out.write(static_cast<sc_int<32>>(reg_data_out_uint.read()));
}

ex_mem::ex_mem(sc_module_name name) : sc_module(name) {
  connect_flip_flop_d(isJump_reg, isJump, isJump_out);
  connect_flip_flop_d(regWrite_reg, regWrite, regWrite_out);
    connect_flip_flop_d(dataRead_reg, dataRead, dataRead_out);
    connect_flip_flop_d(dataWrite_reg, dataWrite, dataWrite_out);
    connect_flip_flop_d(ula_zero_reg, ula_zero, ula_zero_out);
    connect_flip_flop_d(ula_negative_reg, ula_negative, ula_negative_out);
    connect_flip_flop_d(memToReg_reg, memToReg, memToReg_out);
    connect_register(ula_result_reg, ula_result_uint, ula_result_out_uint);
    connect_register(flagSel_reg, flagSel, flagSel_out);
    connect_register(pc_reg, pc, pc_out);
    connect_register(reg_data_reg, reg_data_uint, reg_data_out_uint);
    connect_register(absolute_reg, absolute, absolute_out);
    connect_register(rd_reg, rd, rd_out);
  SC_METHOD(process);
  sensitive << clk;
}
