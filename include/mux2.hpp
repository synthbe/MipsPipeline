#ifndef MUX2_HPP
#define MUX2_HPP

#include "sysc/communication/sc_signal_ports.h"
#include <systemc.h>

template<typename T>
SC_MODULE(mux2) {
  sc_in<bool> sel;
  sc_in<T> A, B;
  sc_out<T> out;

  void process() {
    if(!sel.read()) {
        out.write(A.read());
    } else {
        out.write(B.read());
    }
  }

  SC_CTOR(mux2) {
    SC_METHOD(process);
    sensitive << sel << A << B;
  };
};

#endif // !MUX2_HPP
