#ifndef REGISTRADOR_HPP
#define REGISTRADOR_HPP

#include <systemc.h>

SC_MODULE(registrador) {
  sc_in<bool> clk;
  sc_in<bool> rst;
  sc_in<bool> we; // 0 to write 1 to read
  sc_in<sc_uint<32>> d_in;
  sc_out<sc_uint<32>> d_out;

  void process();

  SC_CTOR(registrador);
};

#endif // !REGISTRADOR_HPP
