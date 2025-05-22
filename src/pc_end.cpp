#include "../include/pc_end.hpp"

void pc_end::process() {
  sc_uint<4> pc_4msbs = pc.read().range(31, 28);
  resposta.write((pc_4msbs, absoluto.read(), 0));
}

pc_end::pc_end(sc_module_name name) : sc_module(name) {
  SC_METHOD(process);
  sensitive << pc << absoluto;
}
