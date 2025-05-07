#include <systemc.h>

SC_MODULE(ULA) {
  sc_in<sc_uint<32>> A, B;
  sc_in<sc_uint<3>> op;
  sc_out<sc_uint<32>> R;
  sc_out<bool> zero, negative, equal;

  void process() {
    sc_uint<32> a = A.read();
    sc_uint<32> b = B.read();
    sc_uint<32> r = 0;
    bool z = false, n = false, e = false;

    switch (op.read()) {
      case 0: r = a + b; break;
      case 1: r = a - b; break;
      case 2: r = a & b; break;
      case 3: r = a | b; break;
      case 4: r = a ^ b; break;
      case 5: r = ~a; break;
      case 6: r = 0, e = (a == b); break;
      default: r = 0;
    }

    R.write(r);
    zero.write(r == 0);
    negative.write(r[31] == 1);
    equal.write(e);
  }

  SC_CTOR(ULA) {
    SC_METHOD(process);
    sensitive << A << B << op;
  }
};
