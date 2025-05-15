#include "../include/banco_reg.hpp"

void banco_reg::write() {
  if (we.read()) {
    regs[rd.read()] = wd.read();
  }
}

void banco_reg::read() {
  rd1.write(regs[rs1.read()]);
  rd2.write(regs[rs2.read()]);
}

banco_reg::banco_reg(sc_module_name name) : sc_module(name) {
  SC_METHOD(write);
  sensitive << clk.pos();

  SC_METHOD(read);
  sensitive << rs1 << rs2;
}

