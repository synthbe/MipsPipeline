#include "../include/id_ex.hpp"
#include "sysc/kernel/sc_module.h"

void id_ex::connect_flip_flop_d(flip_flop_d &ff, sc_in<bool> &in, sc_out<bool> &out) {
  ff.clk(clk);
  ff.rst(rst);
  ff.a(in);
  ff.b(out);
  ff.we(vcc);
}

template<int N>
void id_ex::connect_register(registrador<N> &reg, sc_in<sc_uint<N>> &in, sc_out<sc_uint<N>> &out) {
  reg.clk(clk);
  reg.rst(rst);
  reg.we(vcc);
  reg.d_in(in);
  reg.d_out(out);
}

template<int N>
void id_ex::connect_register(registrador<N> &reg, sc_signal<sc_uint<N>> &in, sc_signal<sc_uint<N>> &out) {
  reg.clk(clk);
  reg.rst(rst);
  reg.we(vcc);
  reg.d_in(in);
  reg.d_out(out);
}

void id_ex::wwrite() {
  read1_uint.write(static_cast<sc_uint<32>>(read1.read()));
  read2_uint.write(static_cast<sc_uint<32>>(read2.read()));
  immediate_uint.write(static_cast<sc_uint<32>>(immediate.read()));

}

void id_ex::read() {
  read1_out.write(static_cast<sc_int<32>>(read1_out_uint.read()));
  read2_out.write(static_cast<sc_int<32>>(read2_out_uint.read()));
  immediate_out.write(static_cast<sc_int<32>>(immediate_out_uint.read()));
}

id_ex::id_ex(sc_module_name name) : sc_module(name) {
  connect_flip_flop_d(isJump_reg, isJump, isJump_out);
  connect_flip_flop_d(regWrite_reg, regWrite, regWrite_out);
  connect_flip_flop_d(op2Sel_reg, op2Sel, op2Sel_out);
  connect_flip_flop_d(dataRead_reg, dataRead, dataRead_out);
  connect_flip_flop_d(dataWrite_reg, dataWrite, dataWrite_out);
  connect_flip_flop_d(memToReg_reg, memToReg, memToReg_out);
  connect_register(opUla_reg, opUla, opUla_out);
  connect_register(flagSel_reg, flagSel, flagSel_out);
  connect_register(read1_reg, read1_uint, read1_out_uint);
  connect_register(read2_reg, read2_uint, read2_out_uint);
  connect_register(immediate_reg, immediate_uint, immediate_out_uint);
  connect_register(pc_reg, pc, pc_out);
  connect_register(rd_reg, rd, rd_out);
  connect_register(rt_reg, rt, rt_out);
  connect_register(rs_reg, rs, rs_out);
  connect_register(absolute_reg, absolute, absolute_out);
  SC_METHOD(wwrite);
  SC_METHOD(read);
}
