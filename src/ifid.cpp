#include "../include/ifid.hpp"

void ifid::process() {
  read1.write(in_inst.read().range(25, 21));
  read2.write(in_inst.read().range(20, 16));
  immediate.write(static_cast<sc_int<16>>(in_inst.read().range(15, 0)));
}

ifid::ifid(sc_module_name name) : sc_module(name) {
    ifid_pc.clk(clk);
    ifid_pc.rst(earth);
    ifid_pc.we(vcc);
    ifid_pc.d_in(in_pc);
    ifid_pc.d_out(out_pc);

    ifid_inst.clk(clk);
    ifid_inst.rst(earth);
    ifid_inst.we(vcc);
    ifid_inst.d_in(in_inst);
    ifid_inst.d_out(out_inst);

  SC_METHOD(process);
  sensitive << clk.pos() << in_pc << in_inst;
}
