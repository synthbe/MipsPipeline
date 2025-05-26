#include "../include/banco_reg.hpp"

void banco_reg::write() {
  while (true) {
    wait(clk.negedge_event());
    if (we.read()){  
      regs[rd.read()].write(wd.read());
    }
  }
}

void banco_reg::read() {
  rd1.write(regs[rs1.read()].read());
  rd2.write(regs[rs2.read()].read());
}

banco_reg::banco_reg(sc_module_name name) : sc_module(name) {
  SC_THREAD(write);
  SC_METHOD(read);
  sensitive << rs1 << rs2;
}


