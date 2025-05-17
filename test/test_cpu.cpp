#include "../include/registrador.hpp"
#include "../include/mem_instrucao.hpp"
#include "../include/somador.hpp"

#include <systemc.h>

SC_MODULE(test_cpu) {
    const int CLOCK_SIZE_NS = 10;
  sc_signal<bool> clk, rst, pcWrite;
  sc_signal<sc_uint<32>> d_in, d_out, fourConstant, pcNextValue, pcCurrValue, palavra;
  sc_signal<bool> resetPc, barrierWrite;
  sc_signal<bool> vcc, earth;


  registrador pc{"pc"};
  mem_instrucao mem_ins{"mem_ins"};
  somador inc{"inc"};

  // Registradores IF/ID
  registrador ifid_pc{"ifid_pc"};
  registrador ifid_inst{"ifid_inst"};
  sc_signal<sc_uint<32>> ifid_pc_saida, ifid_inst_saida;


  void clock_gen() {
    while (true) {
      clk.write(false);
      wait(CLOCK_SIZE_NS/2, SC_NS);
      clk.write(true);
      wait(CLOCK_SIZE_NS/2, SC_NS);
    }
  }

  // A cada ciclo de clock avança uma instrução
  void test() {
    for(int i=0; i<4*10; i++) {
        mem_ins.mem[i] = i;
    }

    for(int i=0; i<5; i++) {
        wait(CLOCK_SIZE_NS, SC_NS);
        std::cout << "Last program counter: " << std::hex << "0x" << ifid_pc_saida.read() << std::endl;
        std::cout << "Curr program counter: " << std::hex << "0x" << pc.d_out.read() << std::endl;
    }

    sc_stop();
  }

  SC_CTOR(test_cpu) : pc("pc"), mem_ins("mem_ins"), inc("inc"), ifid_pc("ifid_pc"), ifid_inst("ifid_inst") {
    pcWrite.write(true);
    barrierWrite.write(true);
    fourConstant.write(4);
    resetPc.write(false);
    vcc.write(true);
    earth.write(false);

    pc.clk(clk);
    pc.rst(resetPc);
    pc.we(pcWrite);
    pc.d_in(pcNextValue);
    pc.d_out(pcCurrValue);

    inc.a(pc.d_out);
    inc.b(fourConstant);
    inc.d_out(pcNextValue);

    mem_ins.endereco(pcCurrValue);
    mem_ins.palavra(palavra);

    ifid_pc.clk(clk);
    ifid_pc.rst(earth);
    ifid_pc.we(vcc);
    ifid_pc.d_in(pcCurrValue);
    ifid_pc.d_out(ifid_pc_saida);

    ifid_inst.clk(clk);
    ifid_inst.rst(earth);
    ifid_inst.we(vcc);
    ifid_inst.d_in(palavra);
    ifid_inst.d_out(ifid_inst_saida);

    SC_THREAD(clock_gen);
    SC_THREAD(test);
  }
};

int sc_main(int argc, char **argv) {
  test_cpu tb("tb");
  sc_start();
  return 0;
}
