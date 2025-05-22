#ifndef REGISTRADOR_HPP
#define REGISTRADOR_HPP

#include <systemc.h>

template<int N = 32>
SC_MODULE(registrador) {
  sc_in<bool> clk;
  sc_in<bool> rst;
  sc_in<bool> we; // 0 to write 1 to read
  sc_in<sc_uint<N>> d_in;
  sc_out<sc_uint<N>> d_out;

  void process() {
    if (rst.read()) {
        d_out.write(0);
    } else if (we.read()) {
        d_out.write(d_in.read());
    }
  };

  SC_CTOR(registrador) {
    SC_METHOD(process);
    sensitive << clk.pos() << rst;
  };
};

#endif // !REGISTRADOR_HPP
