#include "../include/banco_reg.hpp"

void banco_reg::write() {
  while (true) {
    wait();
    if (we.read()) {
      reg = wd.read();
    }
  }
}

void banco_reg::read() {
  rd.write(reg);
}

banco_reg::banco_reg(sc_module_name name) : sc_module(name) {
  SC_METHOD(read);
  sensitive << wd << we;

  SC_CTHREAD(write, clk.pos());
}
