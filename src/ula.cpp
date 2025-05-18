#include "../include/ula.hpp"

void ula::process() {
  sc_int<32> a = A.read();
  sc_int<32> b = B.read();
  sc_int<32> r = 0;
  bool z = false, n = false;

  switch (op.read()) {
    case SOMA: r = a + b; break;
    case SUB: r = a - b; break;
    case AND: r = a & b; break;
    case OR: r = a | b; break;
    case XOR: r = a ^ b; break;
    case NOT: r = ~a; break;
    default: r = 0;
  }

  R.write(r);
  zero.write(r == 0);
  negative.write(r < 0);
}

ula::ula(sc_module_name name) : sc_module(name) {
  SC_METHOD(process);
  sensitive << A << B << op;
}
