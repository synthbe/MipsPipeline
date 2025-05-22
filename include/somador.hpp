#ifndef SOMADOR_HPP
#define SOMADOR_HPP

#include <systemc.h>

SC_MODULE(somador) {
  sc_in<sc_uint<32>> a;
  sc_in<sc_uint<32>> b;
  sc_out<sc_uint<32>> d_out;

  void process();

  SC_CTOR(somador);
};

#endif // !SOMADOR_HPP
