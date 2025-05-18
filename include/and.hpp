#ifndef AND_PORT_HPP
#define AND_PORT_HPP

#include <systemc.h>

SC_MODULE(and_port) {
    sc_in<bool> A, B;
    sc_out<bool> out;

  void process() {
    out.write(A.read() && B.read());
  };

  SC_CTOR(and_port) {
    SC_METHOD(process);
    sensitive << A << B;
  };
};

#endif