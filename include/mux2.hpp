#ifndef MUX2_HPP
#define MUX2_HPP

#include "sysc/communication/sc_signal_ports.h"
#include <systemc.h>

SC_MODULE(mux2) {
  sc_in<sc_uint<2>> sel;
  sc_in<sc_uint<32>> A, B;
  sc_out<sc_uint<32>> out;

  void process();

  SC_CTOR(mux2);
};

#endif // !MUX2_HPP
