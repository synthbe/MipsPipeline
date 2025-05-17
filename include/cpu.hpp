#ifndef CPU_HPP
#define CPU_HPP

#include <systemc.h>
#include "./registrador.hpp"
#include "./mem_instrucao.hpp"
#include "./somador.hpp"

SC_MODULE(cpu) {
  sc_in<bool> clk;

  registrador pc;
  mem_instrucao mem_ins;
  somador incremento;
  
  void process();

  SC_CTOR(cpu);
};

#endif // !CPU_HPP
