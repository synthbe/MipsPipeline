#include "../include/mux2.hpp"
#include <systemc.h>

SC_MODULE(test_mux2) {
  sc_signal<sc_uint<2>> sel;
  sc_signal<sc_uint<32>>  A, B;
  sc_signal<sc_uint<32>> out;

  mux2 uut{"mux2"};

  void test() {
    A.write(10);
    B.write(20);

    for (int i = 0; i < 2; ++i) {
      sel.write(i);
      wait(1, SC_NS);
      std::cout << "sel = " << i << " -> out = " << out.read() << std::endl;
    }

    sc_stop();
  }

  SC_CTOR(test_mux2) {
    uut.sel(sel);
    uut.A(A);
    uut.B(B);
    uut.out(out);

    SC_THREAD(test);
  }
};

int sc_main(int argc, char **argv) {
  test_mux2 tb("tb");
  sc_start();

  return 0;
}
