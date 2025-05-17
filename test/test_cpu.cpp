#include "../include/registrador.hpp"
#include "../include/mem_instrucao.hpp"
#include "../include/somador.hpp"
#include "../include/banco_reg.hpp"
#include "../include/signal_extend.hpp"
#include "../include/parte_controle.hpp"
#include "../include/ifid.hpp"

#include <systemc.h>

SC_MODULE(test_cpu) {
  const int CLOCK_SIZE_NS = 10;
  sc_signal<bool> clk;
  sc_signal<bool> vcc, earth;

  // Primeiro estágio
  registrador pc{"pc"};
  mem_instrucao mem_ins{"mem_ins"};
  somador inc{"inc"};
  sc_signal<sc_uint<32>> fourConstant, pcNextValue, pcCurrValue, palavra;
  sc_signal<bool> resetPc, pcWrite;

  // Registradores IF/ID
  ifid bar_ifid{"bar_ifid"};
    sc_signal<sc_uint<32>> ifid_pc_saida, ifid_inst_saida;
    sc_signal<sc_uint<5>> read1, read2;
    sc_signal<sc_int<16>> immediate;


  // Segundo estágio
  banco_reg b_reg{"b_reg"};
  parte_controle controle{"control"};
  signal_extend sign_ext{"sign_ext"};
  sc_signal<sc_int<32>> ext_immidiate, b_reg_result1, b_reg_result2;

  // Sinais de saída da parte de contole
  sc_signal<bool> isJump, regWrite, op2Sel,
    dataRead, dataWrite, memToReg;
  sc_signal<sc_uint<5>> opUla;
  sc_signal<sc_uint<2>> flagSel;


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

  SC_CTOR(test_cpu) : pc("pc"), mem_ins("mem_ins"), inc("inc"), bar_ifid("bar_ifid") {
    pcWrite.write(true);
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

    bar_ifid.clk(clk);
    bar_ifid.in_pc(pcCurrValue);
    bar_ifid.in_inst(palavra);
    bar_ifid.out_pc(ifid_pc_saida);
    bar_ifid.out_inst(ifid_inst_saida);
    bar_ifid.read1(read1);
    bar_ifid.read2(read2);
    bar_ifid.immediate(immediate);
    bar_ifid.earth(earth);
    bar_ifid.vcc(vcc);

    controle.palavra(ifid_inst_saida);
    controle.isJump(isJump);
    controle.regWrite(regWrite);
    controle.op2Sel(op2Sel);
    controle.dataRead(dataRead);
    controle.dataWrite(dataWrite);
    controle.memToReg(memToReg);
    controle.opUla(opUla);
    controle.flagSel(flagSel);

    sign_ext.d_in(immediate);
    sign_ext.d_out(ext_immidiate);

    b_reg.clk(clk);
    b_reg.we(earth);
    b_reg.rs1(read1);
    b_reg.rs2(read2);
    b_reg.rd(read1); // Temporário
    b_reg.wd(ext_immidiate); // Temporário
    b_reg.rd1(b_reg_result1);
    b_reg.rd2(b_reg_result2);


    SC_THREAD(clock_gen);
    SC_THREAD(test);
  }
};

int sc_main(int argc, char **argv) {
  test_cpu tb("tb");
  sc_start();
  return 0;
}
