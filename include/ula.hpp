#ifndef ULA_HPP
#define ULA_HPP

#include "sysc/communication/sc_signal_ports.h"
#include "sysc/kernel/sc_module.h"
#include <systemc.h>


enum ULAOP {
    SOMA,
    SUB,
    AND,
    OR,
    XOR,
    NOT,
    EQUAL
};

SC_MODULE(ula) {
  sc_in<sc_int<32>> A, B;
  sc_in<sc_uint<11>> op;
  sc_out<sc_int<32>> R;
  sc_out<bool> zero, negative;

  void process();

  SC_CTOR(ula);
};

#endif // !ULA_HPP
