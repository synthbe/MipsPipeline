#ifndef MEM_DADOS_HPP
#define MEM_DADOS_HPP

#include <systemc.h>

SC_MODULE(mem_dados) {
 
  sc_int<32> mem[2048];
 

  sc_in<bool> clk;
  sc_in<bool> dataRead, dataWrite;
  sc_in<sc_int<32>> endereco;
  sc_in<sc_int<32>> dados;

  sc_out<sc_int<32>> resposta;

  void process();

  SC_CTOR(mem_dados);
};

#endif
