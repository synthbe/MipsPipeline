#include "../include/mem_instrucao.hpp"

void mem_instrucao::process() {
    int start = endereco.read();
    palavra.write((mem[start], mem[start+1], mem[start+2], mem[start+3]));
}

mem_instrucao::mem_instrucao(sc_module_name name) : sc_module(name) {
  SC_METHOD(process);
  sensitive << endereco;
}
