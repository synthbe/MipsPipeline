#include "../include/ula.hpp"
#include "sysc/kernel/sc_externs.h"
#include "sysc/kernel/sc_module.h"
#include "systemc.h"
#include "ostream"
#include <iostream>

SC_MODULE(test_ula) {
  sc_signal<sc_uint<32>> A, B, R;
  sc_signal<sc_uint<3>> op;
  sc_signal<bool> zero, negative, equal;

  ula uut{"ula"};

  void test() {
    A.write(10);
    B.write(6);
    op.write(1); // Sub
    wait(5, SC_NS);
    std::cout << "[Sub] (" << A.read() << ", " << B.read() << ") = " << R.read() << std::endl;

    op.write(0); // Sum
    wait(5, SC_NS);
    std::cout << "[Sum] (" << A.read() << ", " << B.read() << ") = " << R.read() << std::endl;

    A.write(36);
    B.write(42);
    op.write(6); // Equal
    wait(5, SC_NS);
    std::cout << "[Equ] (" << A.read() << ", " << B.read() << ") = " << equal.read() << std::endl;

    A.write(42);
    B.write(42);
    op.write(6); // Equal
    wait(5, SC_NS);
    std::cout << "[Equ] (" << A.read() << ", " << B.read() << ") = " << equal.read() << std::endl;
  }

  SC_CTOR(test_ula) : uut("ula") {
    uut.A(A);
    uut.B(B);
    uut.op(op);
    uut.R(R);
    uut.zero(zero);
    uut.negative(negative);
    uut.equal(equal);

    SC_THREAD(test);
  }
};

int sc_main(int argc, char **argv) {
  test_ula tb("tb");
  sc_start();

  return 0;
}
