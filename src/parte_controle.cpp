#include "../include/parte_controle.hpp"
#include "../include/ula.hpp"

void parte_controle::process() {
  sc_uint<6> opcode = palavra.read().range(31, 26);
  sc_uint<2> type = opcode.range(5, 4);

  if(type == OP_TYPES::R_TYPE) { // Tipo R
    sc_uint<11> funct = palavra.read().range(10, 0);
    isJump.write(false);
    regWrite.write(true);
    op2Sel.write(OP2_SEL::RT);
    opUla.write(funct);
    dataRead.write(false);
    dataWrite.write(false);
    regSel.write(REG_SEL::READ2_REG);
    memToReg.write(MEM_TO_REG::ULA_RESULT);
  } else if (type == OP_TYPES::S_TYPE) { // Tipo S (ler/escrever na memoria)
    sc_uint<2> spec = opcode.range(1, 0);
    isJump.write(false);
    op2Sel.write(OP2_SEL::IMEDIATE);
    opUla.write(ULAOP::SOMA);
    memToReg.write(MEM_TO_REG::MEMORY);

    if(spec == S_TYPE_OP::READ) {
        regWrite.write(true);
        dataRead.write(true);
        dataWrite.write(false);
    } else {
        regWrite.write(false);
        dataRead.write(true);
        dataWrite.write(false);
        regSel.write(REG_SEL::WRITE_REG);
    }
  } else if (type == OP_TYPES::J_TYPE) {
    sc_uint<2> spec = opcode.range(1, 0);
    isJump.write(true);
    dataWrite.write(false);
    regWrite.write(false);

    if(spec == J_TYPE_OP::ABSOLUTE) flagSel.write(FLAG_SEL::VCC);
    else if(spec == J_TYPE_OP::IF_ZERO) flagSel.write(FLAG_SEL::ZERO);
    else flagSel.write(FLAG_SEL::NEG);

  } else {
    isJump.write(false);
    regWrite.write(false);
    op2Sel.write(OP2_SEL::RT);
    opUla.write(ULAOP::SOMA);
    dataRead.write(false);
    dataWrite.write(false);
    memToReg.write(MEM_TO_REG::ULA_RESULT);
  }
}

parte_controle::parte_controle(sc_module_name name) : sc_module(name) {
  SC_METHOD(process);
  sensitive << palavra;
}
