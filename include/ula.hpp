#ifndef ULA_HPP
#define ULA_HPP

#include "sysc/communication/sc_signal_ports.h"
#include "sysc/kernel/sc_module.h"
#include <systemc.h>

SC_MODULE(ula) {
  sc_in<sc_uint<32>> A, B;
  sc_in<sc_uint<3>> op;
  sc_out<sc_uint<32>> R;
  sc_out<bool> zero, negative, equal;

  void process();

  SC_CTOR(ula);
};

#endif // !ULA_HPP
