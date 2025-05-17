#include "../include/registrador.hpp"
#include <systemc.h>

SC_MODULE(test_registrador) {
  sc_signal<bool> clk, rst, we;
  sc_signal<sc_uint<32>> d_in, d_out;

  registrador uut{"reg"};

  void clock_gen() {
    while (true) {
      clk.write(false);
      wait(5, SC_NS);
      clk.write(true);
      wait(5, SC_NS);
    }
  }

  void test() {
    rst.write(true);
    we.write(false);
    d_in.write(0xAAAAAAAA);
    wait(10, SC_NS);
    std::cout << "Current value in d_out: 0x" << std::hex << d_out.read() << std::endl;

    rst.write(false);
    wait(10, SC_NS);

    we.write(true);
    d_in.write(0x12345678);
    wait(10, SC_NS);
    std::cout << "Current value in d_out: 0x" << std::hex << d_out.read() << std::endl;

    d_in.write(0xDEADBEEF);
    wait(10, SC_NS);

    we.write(false);
    d_in.write(0x0);
    wait(10, SC_NS);

    std::cout << "Final value in d_out: 0x" << std::hex << d_out.read() << std::endl;

    sc_stop();
  }

  SC_CTOR(test_registrador) : uut("reg") {
    uut.clk(clk);
    uut.rst(rst);
    uut.we(we);
    uut.d_in(d_in);
    uut.d_out(d_out);

    SC_THREAD(clock_gen);
    SC_THREAD(test);
  }
};

int sc_main(int argc, char **argv) {
  test_registrador tb("tb");
  sc_start();
  return 0;
}
