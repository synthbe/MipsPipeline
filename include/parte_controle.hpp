#ifndef PARTE_CONTROLE_HPP
#define PARTE_CONTROLE_HPP

#include <systemc.h>


enum OP2_SEL {
    RT,
    IMEDIATE,
};

enum FLAG_SEL {
    VCC,
    ZERO,
    NEG,
    EARTH,
};

enum MEM_TO_REG {
    ULA_RESULT,
    MEMORY
};

enum OP_TYPES {
    STUB,
    R_TYPE,
    S_TYPE,
    J_TYPE
};

enum S_TYPE_OP {
    READ,
    WRITE
};

enum J_TYPE_OP {
    ABSOLUTE,
    IF_ZERO,
    IF_NEG
};

SC_MODULE(parte_controle) {
  sc_in<sc_uint<32>> palavra;

  sc_out<bool> isJump, regWrite, op2Sel,
    dataRead, dataWrite, memToReg;
  sc_out<sc_uint<11>> opUla;
  sc_out<sc_uint<2>> flagSel;

  void process();

  SC_CTOR(parte_controle);
};

#endif // !PARTE_CONTROLE_HPP
