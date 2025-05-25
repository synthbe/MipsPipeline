#include "../include/carregar.hpp"

void carregar(sc_uint<8> *mem_instrucao, sc_int<32> *mem_dados) {
	mem_dados[1] = 10;
	mem_dados[2] = 30;
	mem_dados[3] = 50;
	mem_instrucao[4] = 0b10000000;
	mem_instrucao[5] = 0b01000000;
	mem_instrucao[6] = 0b00000000;
	mem_instrucao[7] = 0b00000001;
	mem_instrucao[8] = 0b10000000;
	mem_instrucao[9] = 0b01100000;
	mem_instrucao[10] = 0b00000000;
	mem_instrucao[11] = 0b00000010;
	mem_instrucao[12] = 0b01000000;
	mem_instrucao[13] = 0b01100001;
	mem_instrucao[14] = 0b00010000;
	mem_instrucao[15] = 0b00000000;
};
