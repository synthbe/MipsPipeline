#include "../include/flip_flop_d.hpp"

void flip_flop_d::process() {

  if (rst.read()) {
    b.write(0);
  } else {
    b.write(a.read());
  }

}

flip_flop_d::flip_flop_d(sc_module_name name) : sc_module(name) {
  SC_METHOD(process);
  sensitive << clk.pos() << rst;
}
