#include "../include/mux_controle.hpp"

void mux_controle::process() {
  if(!sel.read()) {
    isJump_out.write(isJump.read());
    regWrite_out.write(regWrite.read());
    op2Sel_out.write(op2Sel.read());
    dataRead_out.write(dataRead.read());
    dataWrite_out.write(dataWrite.read());
    memToReg_out.write(memToReg.read());
    opUla_out.write(opUla.read());
    flagSel_out.write(flagSel.read());
  } else {
    isJump_out.write(false);
    regWrite_out.write(false);
    op2Sel_out.write(0);
    dataRead_out.write(false);
    dataWrite_out.write(false);
    memToReg_out.write(0);
    opUla_out.write(0);
    flagSel_out.write(0);
  }
}
mux_controle::mux_controle(sc_module_name name) : sc_module(name) {
  SC_METHOD(process);
  sensitive << sel
   << isJump
   << regWrite
   << op2Sel
   << dataRead
   << dataWrite
   << memToReg
   << opUla
   << flagSel;
}