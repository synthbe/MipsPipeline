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
void mem_wb::connect_register(registrador<N> &reg, sc_signal<sc_uint<N>> &in, sc_signal<sc_uint<N>> &out) {
  reg.clk(clk);
  reg.rst(rst);
  reg.we(vcc);
  reg.d_in(in);
  reg.d_out(out);
}

void mem_wb::process() {
    ula_result_uint.write(static_cast<sc_uint<32>>(ula_result.read()));
    ula_result_out.write(static_cast<sc_int<32>>(ula_result_out_uint.read()));

    mem_data_uint.write(static_cast<sc_uint<32>>(mem_data.read()));
    mem_data_out.write(static_cast<sc_int<32>>(mem_data_out_uint.read()));
}

mem_wb::mem_wb(sc_module_name name) : sc_module(name) {
  connect_flip_flop_d(regWrite_reg, regWrite, regWrite_out);
    connect_flip_flop_d(memToReg_reg, memToReg, memToReg_out);
    connect_register(ula_result_reg, ula_result_uint, ula_result_out_uint);
    connect_register(mem_data_reg, mem_data_uint, mem_data_out_uint);
    connect_register(rd_reg, rd, rd_out);
  SC_METHOD(process);
  sensitive << clk.pos();
}
