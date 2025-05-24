#ifndef FLIP_FLOP_D_HPP
#define FLIP_FLOP_D_HPP

#include "sysc/communication/sc_signal_ports.h"
#include "sysc/kernel/sc_module.h"
#include <systemc.h>

SC_MODULE(flip_flop_d) {
  sc_in<bool> clk;
  sc_in<bool> rst;
  sc_in<bool> we; // 1 for write
  sc_in<bool> a; // entrada
  sc_out<bool> b; // saída;

  sc_signal<bool> storage;

  void wwrite();

  void read();

  SC_CTOR(flip_flop_d);
};

#endif // !FLIP_FLOP_D_HPP
