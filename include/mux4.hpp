#ifndef MUX4_HPP
#define MUX4_HPP

#include "sysc/communication/sc_signal_ports.h"
#include "sysc/kernel/sc_module.h"
#include <systemc.h>

SC_MODULE(mux4) {
  sc_in<sc_uint<2>> sel;
  sc_in<sc_uint<32>> A, B, C, D;
  sc_out<sc_uint<32>> out;

  void process();

  SC_CTOR(mux4);
};

#endif // !MUX4_HPP
