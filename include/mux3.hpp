#ifndef MUX3_HPP
#define MUX3_HPP

#include "sysc/communication/sc_signal_ports.h"
#include <systemc.h>

SC_MODULE(mux3) {
  sc_in<sc_uint<3>> sel;
  sc_in<sc_uint<32>> A, B, C;
  sc_out<sc_uint<32>> out;

  void process();

  SC_CTOR(mux3);
};

#endif // !MUX3_HPP
