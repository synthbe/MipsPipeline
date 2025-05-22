#ifndef MUX4_HPP
#define MUX4_HPP

#include "sysc/communication/sc_signal_ports.h"
#include "sysc/kernel/sc_module.h"
#include <systemc.h>

template <typename T>
SC_MODULE(mux4) {
  sc_in<sc_uint<2>> sel;
  sc_in<T> A, B, C, D;
  sc_out<T> out;

  void process() {
    switch (sel.read()) {
        case 0: out.write(A.read()); break;
        case 1: out.write(B.read()); break;
        case 2: out.write(C.read()); break;
        case 3: out.write(D.read()); break;
        default: out.write(0); break;
    }
  };

  SC_CTOR(mux4) {
    SC_METHOD(process);
    sensitive << sel << A << B << C << D;
  };
};

#endif // !MUX4_HPP
