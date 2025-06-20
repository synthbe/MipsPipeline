#include "../include/if_id.hpp"

void if_id::process() {
  write1.write(ifid_inst.d_out.read().range(25, 21));
  read1.write(ifid_inst.d_out.read().range(20, 16));
  read2.write(ifid_inst.d_out.read().range(15, 11));
  immediate.write(static_cast<sc_int<16>>(ifid_inst.d_out.read().range(15, 0)));
  absolute.write(ifid_pc.d_out.read().range(25, 0));
}

if_id::if_id(sc_module_name name) : sc_module(name) {
    ifid_pc.clk(clk);
    ifid_pc.rst(rst);
    ifid_pc.we(if_id_write);
    ifid_pc.d_in(in_pc);
    ifid_pc.d_out(out_pc);

    ifid_inst.clk(clk);
    ifid_inst.rst(rst);
    ifid_inst.we(if_id_write);
    ifid_inst.d_in(in_inst);
    ifid_inst.d_out(out_inst);

  SC_METHOD(process);
  sensitive << clk;
}
