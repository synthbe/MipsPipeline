#include "../include/mux3.hpp"

void mux3::process() {
  switch (sel.read()) {
    case 0: out.write(A.read()); break;
    case 1: out.write(B.read()); break;
    case 2: out.write(C.read()); break;
    default: out.write(0); break;
  }
}

mux3::mux3(sc_module_name name) : sc_module(name) {
  SC_METHOD(process);
  sensitive << sel << A << B << C;
}


