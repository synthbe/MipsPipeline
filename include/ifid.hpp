#ifndef IFID_HPP
#define IFID_HPP

#include "registrador.hpp"
#include <systemc.h>

SC_MODULE(ifid) {
  sc_in<bool> clk;
  sc_in<bool> earth, vcc;
  sc_in<sc_uint<32>> in_pc, in_inst;
  sc_out<sc_uint<32>> out_pc, out_inst;
  sc_out<sc_uint<5>> read1, read2;
  sc_out<sc_int<16>> immediate;

  registrador ifid_pc{"ifid_pc"};
  registrador ifid_inst{"ifid_inst"};


  void process();

  SC_CTOR(ifid);
};

#endif // !IFID_HPP
