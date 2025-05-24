#include "../include/flip_flop_d.hpp"

void flip_flop_d::wwrite() {
  while(true) {
    wait(clk.posedge_event());
    if(rst.read()) {
        storage.write(false);
    } else if (we.read()) {
        storage.write(a.read());
    }
  }
}

void flip_flop_d::read() {
    while(true) {
        wait(clk.negedge_event());
        b.write(storage.read());
    }
}



flip_flop_d::flip_flop_d(sc_module_name name) : sc_module(name) {
  SC_THREAD(wwrite);
  SC_THREAD(read);
}
