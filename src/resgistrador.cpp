#include "../include/registrador.hpp"

void registrador::process() {
  if (rst.read()) {
    d_out.write(0);
  } else if (we.read()) {
    d_out.write(d_in.read());
  }
}

registrador::registrador(sc_module_name name) : sc_module(name) {
  SC_METHOD(process);
  sensitive << clk.pos();
}
