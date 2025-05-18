#include "../include/mux4.hpp"
#include <systemc.h>

SC_MODULE(test_mux4) {
  sc_signal<sc_uint<2>> sel;
  sc_signal<sc_uint<32>> A, B, C, D;
  sc_signal<sc_uint<32>> out;

  mux4<sc_uint<32>> uut{"mux4"};

  void test() {
    A.write(10);
    B.write(20);
    C.write(30);
    D.write(40);

    for (int i = 0; i < 4; ++i) {
      sel.write(i);
      wait(1, SC_NS);
      std::cout << "sel = " << i << " -> out = " << out.read() << std::endl;
    }

    sc_stop();
  }

  SC_CTOR(test_mux4) {
    uut.sel(sel);
    uut.A(A);
    uut.B(B);
    uut.C(C);
    uut.D(D);
    uut.out(out);

    SC_THREAD(test);
  }
};

int sc_main(int argc, char **argv) {
  test_mux4 tb("tb");
  sc_start();

  return 0;
}
