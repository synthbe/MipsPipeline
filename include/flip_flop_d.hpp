#ifndef FLIP_FLOP_D_HPP
#define FLIP_FLOP_D_HPP

#include "sysc/communication/sc_signal_ports.h"
#include "sysc/kernel/sc_module.h"
#include <systemc.h>

SC_MODULE(flip_flop_d) {
  sc_in<bool> clk;
  sc_in<bool> rst;
  sc_in<bool> a;
  sc_out<bool> b;

  void process();

  SC_CTOR(flip_flop_d);
};

#endif // !FLIP_FLOP_D_HPP
