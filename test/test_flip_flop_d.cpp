#include "../include/flip_flop_d.hpp"
#include <systemc.h>

SC_MODULE(test_flip_flop_d) {
  sc_signal<bool> clk, rst, a, b;

  flip_flop_d uut{"flip_flop_d"};

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
    a.write(false);
    wait(10, SC_NS);  // reset ativo
    rst.write(false);

    // Primeiro pulso de clock com a = 1
    a.write(true);
    wait(10, SC_NS);
    std::cout << "[1] b = " << b.read() << std::endl;

    // Segundo pulso com a = 0
    a.write(false);
    wait(10, SC_NS);
    std::cout << "[2] b = " << b.read() << std::endl;

    // Terceiro pulso com a = 1, mas reset ativado
    a.write(true);
    rst.write(true);
    wait(10, SC_NS);
    std::cout << "[3] b (depois do reset) = " << b.read() << std::endl;

    sc_stop();
  }

  SC_CTOR(test_flip_flop_d) : uut("flip_flop_d") {
    uut.clk(clk);
    uut.rst(rst);
    uut.a(a);
    uut.b(b);

    SC_THREAD(clock_gen);
    SC_THREAD(test);
  }
};

int sc_main(int argc, char** argv) {
  test_flip_flop_d tb("tb");
  sc_start();
  return 0;
}
