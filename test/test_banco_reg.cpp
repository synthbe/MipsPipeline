#include "../include/banco_reg.hpp"
#include "sysc/communication/sc_signal.h"
#include "sysc/kernel/sc_externs.h"
#include "sysc/kernel/sc_module.h"
#include "sysc/kernel/sc_simcontext.h"
#include "sysc/kernel/sc_time.h"
#include <ostream>
#include <systemc.h>

SC_MODULE(test_banco_reg) {
  sc_signal<bool> clk, we;
  sc_signal<sc_uint<5>> rs1, rs2, rd;
  sc_signal<sc_uint<32>> wd;
  sc_signal<sc_uint<32>> rd1, rd2;

  banco_reg uut{"banco_reg"};

  void clock_gen() {
    while (true) {
      clk.write(false);
      wait(5, SC_NS);
      clk.write(true);
      wait(5, SC_NS);
    }
  }

  void test() {
    we.write(true);
    rd.write(1);
    wd.write(56);
    wait(5, SC_NS);

    we.write(false);
    rs1.write(1);
    rs2.write(0);
    wait(5, SC_NS);

    std::cout << "rd1 (reg[1]) = " << rd1.read() << std::endl;
    std::cout << "rd2 (reg[0]) = " << rd2.read() << std::endl;

    sc_stop();
  }

  SC_CTOR(test_banco_reg) : uut("banco_reg") {
    uut.clk(clk);
    uut.we(we);
    uut.rs1(rs1);
    uut.rs2(rs2);
    uut.rd(rd);
    uut.wd(wd);
    uut.rd1(rd1);
    uut.rd2(rd2);

    SC_THREAD(clock_gen);
    SC_THREAD(test);
  }
};

int sc_main(int argc, char **argv) {
  test_banco_reg tb("tb");
  sc_start();

  return 0;
}
