#ifndef MEM_INSTRUCAO_HPP
#define MEM_INSTRUCAO_HPP

#include <systemc.h>

SC_MODULE(mem_instrucao) {
  sc_uint<8> mem[2048];

  sc_in<sc_uint<32>> endereco;
  sc_out<sc_uint<32>> palavra;

  void process();

  SC_CTOR(mem_instrucao);
};

#endif // !MEM_INSTRUCAO_HPP
