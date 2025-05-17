#include "../include/banco_reg.hpp"

void banco_reg::write() {
  while (true) {
    wait();
    if (we.read() && rd.read() != 0){  
      regs[rd.read()] = wd.read();
    }
  }
}

void banco_reg::read() {
  rd1.write(regs[rs1.read()]);
  rd2.write(regs[rs2.read()]);
}

banco_reg::banco_reg(sc_module_name name) : sc_module(name) {
  SC_CTHREAD(write, clk.pos());
  SC_METHOD(read);
  sensitive << rs1 << rs2;
}


