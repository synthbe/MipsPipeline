#ifndef PC_END_HPP
#define PC_END_HPP

#include <systemc.h>

SC_MODULE(pc_end) {
  sc_in<sc_uint<32>> pc;
  sc_in<sc_uint<26>> absoluto;

  sc_out<sc_uint<32>> resposta;

  void process();

  SC_CTOR(pc_end);
};

#endif