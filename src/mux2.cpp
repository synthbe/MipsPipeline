#include "../include/mux2.hpp"
#include "sysc/kernel/sc_module.h"
#include "sysc/kernel/sc_module_name.h"

void mux2::process() {
  switch (sel.read()) {
    case 0: out.write(A.read()); break;
    case 1: out.write(B.read()); break;
    default: out.write(0); break;
  }
}

mux2::mux2(sc_module_name name) : sc_module(name) {
  SC_METHOD(process);
  sensitive << sel << A << B;
}
