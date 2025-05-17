#include "../include/somador.hpp"

void somador::process() {
  d_out.write(a.read() + b.read());
}

somador::somador(sc_module_name name) : sc_module(name) {
  SC_METHOD(process);
  sensitive << a << b;
}
