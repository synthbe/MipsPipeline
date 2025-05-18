#include "../include/signal_extend.hpp"

void signal_extend::process() {
  d_out.write(d_in.read());
}

signal_extend::signal_extend(sc_module_name name) : sc_module(name) {
  SC_METHOD(process);
  sensitive << d_in;
}
