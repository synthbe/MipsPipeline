#ifndef SIGNAL_EXTEND_HPP
#define SIGNAL_EXTEND_HPP

#include <systemc.h>

SC_MODULE(signal_extend) {
  sc_in<sc_int<16>> d_in;
  sc_out<sc_int<32>> d_out;

  void process();

  SC_CTOR(signal_extend);
};

#endif // !SIGNAL_EXTEND_HPP
