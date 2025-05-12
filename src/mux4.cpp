#include "../include/mux4.hpp"

void mux4::process() {
  switch (sel.read()) {
    case 0: out.write(A.read()); break;
    case 1: out.write(B.read()); break;
    case 2: out.write(C.read()); break;
    case 3: out.write(D.read()); break;
    default: out.write(0); break;
  }
}

mux4::mux4(sc_module_name name) : sc_module(name) {
  SC_METHOD(process);
  sensitive << sel << A << B << C << D;
}
