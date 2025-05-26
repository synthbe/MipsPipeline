#ifndef REGISTRADOR_INT_HPP
#define REGISTRADOR_INT_HPP

#include <systemc.h>

template<int N = 32>
SC_MODULE(registrador_int) {
  sc_in<bool> clk;
  sc_in<bool> rst;
  sc_in<bool> we; // 1 to write
  sc_in<sc_int<N>> d_in;
  sc_out<sc_int<N>> d_out;

  sc_signal<sc_int<N>> storage;


  void wwrite() {
    while(true) {
        wait(clk.posedge_event());
        if(rst.read()) {
            storage.write(0);
        } else if (we.read()) {
            storage.write(d_in.read());
        }
    }
  };

  void read() {
    while(true) {
        wait(clk.negedge_event());
        d_out.write(storage.read());
    }
  }

  SC_CTOR(registrador_int) {
    SC_THREAD(wwrite);
    SC_THREAD(read);
  };
};

#endif // !REGISTRADOR_HPP
