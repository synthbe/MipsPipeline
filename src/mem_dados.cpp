#include "../include/mem_dados.hpp"

void mem_dados::process() {
  if (dataRead.read()) {
    resposta.write(mem[endereco.read()]);
  } else if (dataWrite.read()) {
    mem[endereco.read()] = dados.read();
  }
}

mem_dados::mem_dados(sc_module_name name) : sc_module(name) {
  SC_METHOD(process);
  sensitive << clk.pos();
}