#ifndef BANCO_REG_HPP
#define BANCO_REG_HPP

#include <systemc.h>

SC_MODULE(banco_reg) {
  sc_in<bool> clk;
  sc_in<bool> we;
  sc_in<sc_uint<32>> wd;
  sc_out<sc_uint<32>> rd;

  sc_uint<32> reg;

  void write();
  void read();

  SC_CTOR(banco_reg);
};

#endif // !BANCO_REG_HPP
