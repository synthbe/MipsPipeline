#ifndef BANCO_REG_HPP
#define BANCO_REG_HPP

#include <systemc.h>

SC_MODULE(banco_reg) {
  sc_in<bool> clk;
  sc_in<bool> we;

  sc_in<sc_uint<5>> rs1, rs2, rd;
  sc_in<sc_int<32>> wd;
  sc_out<sc_int<32>> rd1, rd2;

  sc_signal<sc_int<32>> regs[32];

  void write();
  void read();

  SC_CTOR(banco_reg);
};

#endif // !BANCO_REG_HPP

