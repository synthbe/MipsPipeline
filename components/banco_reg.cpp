#include <systemc.h>

SC_MODULE(banco_reg) {
  sc_in<bool> clk;
  sc_in<bool> we;

  sc_in<sc_uint<5>> rs1, rs2, rd;
  sc_in<sc_uint<32>> wd;
  sc_out<sc_uint<32>> rd1, rd2;

  sc_uint<32> regs[32];

  void read() {
    rd1.write(regs[rs1.read()]);
    rd2.write(regs[rs2.read()]);
  }

  void write() {
    if (we.read() && rd.read() != 0)
      regs[rd.read()] = wd.read();
  }

  SC_CTOR(banco_reg) {
    SC_METHOD(read);
    sensitive << rs1 << rs2;

    SC_METHOD(write);
    sensitive << clk.pos();
  }
};
