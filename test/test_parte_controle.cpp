#include "../include/parte_controle.hpp"
#include "../include/utils.hpp"
#include <systemc.h>

SC_MODULE(test_parte_controle) {
  sc_signal<sc_uint<32>> palavra;

  sc_signal<bool> isJump, regWrite, op2Sel,
    dataRead, dataWrite, memToReg;
  sc_signal<sc_uint<5>> opUla;
  sc_signal<sc_uint<2>> flagSel;

  parte_controle uut{"uut"};

  void print_signals(sc_uint<32> &signal_value) {
    palavra.write(signal_value);
    wait(10, SC_NS);

    std::cout << "----------------------------------------" << std::endl;
    std::cout << "isJump: " << isJump.read() << std::endl;
    std::cout << "regWrite: " << regWrite.read() << std::endl;
    std::cout << "op2Sel: " << op2Sel.read() << std::endl;
    std::cout << "dataRead: " << dataRead.read() << std::endl;
    std::cout << "dataWrite: " << dataWrite.read() << std::endl;
    std::cout << "memToReg: " << memToReg.read() << std::endl;
    std::cout << "opUla: " << opUla.read() << std::endl;
    std::cout << "flagSel: " << flagSel.read() << std::endl;
    std::cout << "----------------------------------------" << std::endl;
  }

  void test() {
    sc_uint<32> r_type = "010000_00010_00100_00001_00000000000"_u32;
    sc_uint<32> s_type_read = "100000_00010_00100_0000000000000000"_u32;
    sc_uint<32> s_type_write = "100001_00010_00100_0000000000000000"_u32;
    sc_uint<32> jump = "110000_00000000000000000000000000"_u32;
    sc_uint<32> jump_zero = "110001_00000000000000000000000000"_u32;
    sc_uint<32> jump_neg = "110010_00010001000000000000000000"_u32;

    print_signals(r_type);
    print_signals(s_type_read);
    print_signals(s_type_write);
    print_signals(jump);
    print_signals(jump_zero);
    print_signals(jump_neg);

    sc_stop();
  }

  SC_CTOR(test_parte_controle) : uut("uut") {
    uut.palavra(palavra);
    uut.isJump(isJump);
    uut.regWrite(regWrite);
    uut.op2Sel(op2Sel);
    uut.dataRead(dataRead);
    uut.dataWrite(dataWrite);
    uut.memToReg(memToReg);
    uut.opUla(opUla);
    uut.flagSel(flagSel);
    SC_THREAD(test);
  }
};

int sc_main(int argc, char **argv) {
  test_parte_controle tb("tb");
  sc_start();
  return 0;
}
