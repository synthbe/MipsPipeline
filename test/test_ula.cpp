#include "../include/ula.hpp"
#include "sysc/kernel/sc_externs.h"
#include "sysc/kernel/sc_module.h"
#include "systemc.h"
#include "ostream"
#include <iostream>

SC_MODULE(test_ula) {
  sc_signal<sc_int<32>> A, B, R;
  sc_signal<sc_uint<11>> op;
  sc_signal<bool> zero, negative;

  ula uut{"ula"};

  void test() {
    A.write(10);
    B.write(6);
    op.write(1); // Sub
    wait(5, SC_NS);
    std::cout << "[SUB] (" << A.read() << ", " << B.read() << ") = " << R.read() << " Negative " << negative.read() << std::endl;

    A.write(10);
    B.write(9);
    wait(5, SC_NS);
    std::cout << "[SUB] (" << A.read() << ", " << B.read() << ") = " << R.read() << " Zero " << zero.read() << std::endl;

    A.write(9);
    B.write(9);
    op.write(1); // Sub
    wait(5, SC_NS);
    std::cout << "[SUB] (" << A.read() << ", " << B.read() << ") = " << R.read() << " Zero " << zero.read() << std::endl;


    A.write(6);
    B.write(10);
    op.write(1); // Sub
    wait(5, SC_NS);
    std::cout << "[SUB] (" << A.read() << ", " << B.read() << ") = " << R.read() << " Negative " << negative.read() << std::endl;
  }

  SC_CTOR(test_ula) : uut("ula") {
    uut.A(A);
    uut.B(B);
    uut.op(op);
    uut.R(R);
    uut.zero(zero);
    uut.negative(negative);

    SC_THREAD(test);
  }
};

int sc_main(int argc, char **argv) {
  test_ula tb("tb");
  sc_start();

  return 0;
}
