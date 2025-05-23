#ifndef IFID_HPP
#define IFID_HPP

#include "registrador.hpp"
#include <systemc.h>

SC_MODULE(if_id) {
  sc_in<bool> clk;
  sc_in<bool> rst;
  sc_in<bool> earth, vcc;
  sc_in<bool> if_id_write;
  sc_in<sc_uint<32>> in_pc, in_inst;
  sc_out<sc_uint<32>> out_pc, out_inst;
  sc_out<sc_uint<5>> read1, read2, write1;
  sc_out<sc_int<16>> immediate;
  sc_out<sc_uint<26>> absolute;

  registrador<32> ifid_pc{"ifid_pc"};
  registrador<32> ifid_inst{"ifid_inst"};


  void process();

  SC_CTOR(if_id);
};

#endif // !IFID_HPP
