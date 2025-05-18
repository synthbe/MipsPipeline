#include "../include/registrador.hpp"
#include "../include/mem_instrucao.hpp"
#include "../include/somador.hpp"
#include "../include/banco_reg.hpp"
#include "../include/signal_extend.hpp"
#include "../include/parte_controle.hpp"
#include "../include/if_id.hpp"
#include "../include/id_ex.hpp"
#include "../include/ula.hpp"
#include "../include/mux2.hpp"
#include "../include/ex_mem.hpp"

#include <systemc.h>

SC_MODULE(test_cpu) {
  const int CLOCK_SIZE_NS = 10;
  sc_signal<bool> clk;
  sc_signal<bool> vcc, earth;

  // Primeiro estágio
  registrador<32> pc{"pc"};
  mem_instrucao mem_ins{"mem_ins"};
  somador inc{"inc"};
  sc_signal<sc_uint<32>> fourConstant, pcNextValue, pcCurrValue, palavra;
  sc_signal<bool> resetPc, pcWrite;

  // Registradores IF/ID
  if_id bar_if_id{"bar_if_id"};
    sc_signal<sc_uint<32>> ifid_pc_saida, ifid_inst_saida;
    sc_signal<sc_uint<5>> read1, read2, write1;
    sc_signal<sc_int<16>> immediate;


  // Segundo estágio
  banco_reg b_reg{"b_reg"};
  parte_controle controle{"control"};
  signal_extend sign_ext{"sign_ext"};
  sc_signal<sc_int<32>> ext_immidiate, b_reg_result1, b_reg_result2;

  // Sinais de saída da parte de contole
  sc_signal<bool> isJump, regWrite, op2Sel,
    dataRead, dataWrite, memToReg;
  sc_signal<sc_uint<11>> opUla;
  sc_signal<sc_uint<2>> flagSel;

  id_ex bar_id_ex{"bar_id_ex"};

    sc_signal<bool> id_ex_isJump_out, id_ex_regWrite_out, id_ex_op2Sel_out,
      id_ex_dataRead_out, id_ex_dataWrite_out, id_ex_memToReg_out;
    sc_signal<sc_uint<11>> id_ex_opUla_out;
    sc_signal<sc_uint<2>> id_ex_flagSel_out;
    sc_signal<sc_int<32>> id_ex_read1_out, id_ex_read2_out, id_ex_immediate_out;
    sc_signal<sc_uint<32>> id_ex_pc_out;
    sc_signal<sc_uint<5>> id_ex_rd_out, id_ex_rt_out, id_ex_rs_out;

  // Terceiro estágio
  ula ula_ex{"ula_ex"};
  mux2<sc_int<32>> op2_mux{"op2_mux"};
  sc_signal<sc_int<32>> op2_mux_out;
  sc_signal<sc_int<32>> ula_result_out;
  sc_signal<bool> ula_zero_out, ula_negative_out;

  ex_mem bar_ex_mem{"bar_ex_mem"};
  sc_signal<bool> ex_mem_isJump_out, ex_mem_regWrite_out,
    ex_mem_dataRead_out, ex_mem_dataWrite_out, ex_mem_memToReg_out;
  sc_signal<sc_uint<2>> ex_mem_flagSel_out;
  sc_signal<sc_uint<32>> ex_mem_pc_out;
  sc_signal<sc_int<32>> ex_mem_ula_result_out, ex_mem_reg_data_out;
  sc_signal<bool> ex_mem_ula_zero_out, ex_mem_ula_negative_out;

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
        std::cout << "Last last last program counter: " << std::hex << "0x" << ex_mem_pc_out.read() << std::endl;
        std::cout << "Last last program counter: " << std::hex << "0x" << id_ex_pc_out.read() << std::endl;
        std::cout << "Last program counter: " << std::hex << "0x" << ifid_pc_saida.read() << std::endl;
        std::cout << "Curr program counter: " << std::hex << "0x" << pc.d_out.read() << std::endl;
    }

    sc_stop();
  }

  SC_CTOR(test_cpu) : 
    pc("pc"), 
    mem_ins("mem_ins"), 
    inc("inc"), 
    bar_if_id("bar_if_id"), 
    ula_ex("ula_ex"), 
    op2_mux("op2_mux"), 
    b_reg("b_reg"), 
    controle("control"), 
    sign_ext("sign_ext"),
    bar_id_ex("bar_id_ex")
  {
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

    bar_if_id.clk(clk);
    bar_if_id.earth(earth);
    bar_if_id.vcc(vcc);
    bar_if_id.in_pc(pcCurrValue);
    bar_if_id.in_inst(palavra);
    bar_if_id.out_pc(ifid_pc_saida);
    bar_if_id.out_inst(ifid_inst_saida);
    bar_if_id.read1(read1);
    bar_if_id.read2(read2);
    bar_if_id.write1(write1);
    bar_if_id.immediate(immediate);

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

    bar_id_ex.clk(clk);
    bar_id_ex.rst(earth); // Temporário
    bar_id_ex.earth(earth);
    bar_id_ex.vcc(vcc);
    bar_id_ex.isJump(isJump);
    bar_id_ex.regWrite(regWrite);
    bar_id_ex.op2Sel(op2Sel);
    bar_id_ex.dataRead(dataRead);
    bar_id_ex.dataWrite(dataWrite);
    bar_id_ex.memToReg(memToReg);
    bar_id_ex.opUla(opUla);
    bar_id_ex.flagSel(flagSel);
    bar_id_ex.read1(b_reg_result1);
    bar_id_ex.read2(b_reg_result2);
    bar_id_ex.immediate(ext_immidiate);
    bar_id_ex.pc(ifid_pc_saida);
    bar_id_ex.rd(write1);
    bar_id_ex.rt(read1);
    bar_id_ex.rs(read2);

    bar_id_ex.isJump_out(id_ex_isJump_out);
    bar_id_ex.regWrite_out(id_ex_regWrite_out);
    bar_id_ex.op2Sel_out(id_ex_op2Sel_out);
    bar_id_ex.dataRead_out(id_ex_dataRead_out);
    bar_id_ex.dataWrite_out(id_ex_dataWrite_out);
    bar_id_ex.memToReg_out(id_ex_memToReg_out);
    bar_id_ex.opUla_out(id_ex_opUla_out);
    bar_id_ex.flagSel_out(id_ex_flagSel_out);
    bar_id_ex.read1_out(id_ex_read1_out);
    bar_id_ex.read2_out(id_ex_read2_out);
    bar_id_ex.immediate_out(id_ex_immediate_out);
    bar_id_ex.pc_out(id_ex_pc_out);
    bar_id_ex.rd_out(id_ex_rd_out);
    bar_id_ex.rt_out(id_ex_rt_out);
    bar_id_ex.rs_out(id_ex_rs_out);

    op2_mux.sel(id_ex_op2Sel_out);
    op2_mux.A(id_ex_read2_out);
    op2_mux.B(id_ex_immediate_out);
    op2_mux.out(op2_mux_out);

    ula_ex.A(id_ex_read1_out);
    ula_ex.B(op2_mux_out);
    ula_ex.op(id_ex_opUla_out);
    ula_ex.R(ula_result_out);
    ula_ex.zero(ula_zero_out);
    ula_ex.negative(ula_negative_out);

    bar_ex_mem.clk(clk);
    bar_ex_mem.rst(earth); // Temporário
    bar_ex_mem.earth(earth);
    bar_ex_mem.vcc(vcc);
    bar_ex_mem.isJump(id_ex_isJump_out);
    bar_ex_mem.regWrite(id_ex_regWrite_out);
    bar_ex_mem.dataRead(id_ex_dataRead_out);
    bar_ex_mem.dataWrite(id_ex_dataWrite_out);
    bar_ex_mem.memToReg(id_ex_memToReg_out);
    bar_ex_mem.flagSel(id_ex_flagSel_out);
    bar_ex_mem.ula_zero(ula_zero_out);
    bar_ex_mem.ula_negative(ula_negative_out);
    bar_ex_mem.ula_result(ula_result_out);
    bar_ex_mem.reg_data(id_ex_read2_out);
    bar_ex_mem.pc(id_ex_pc_out);

    bar_ex_mem.isJump_out(ex_mem_isJump_out);
    bar_ex_mem.regWrite_out(ex_mem_regWrite_out);
    bar_ex_mem.dataRead_out(ex_mem_dataRead_out);
    bar_ex_mem.dataWrite_out(ex_mem_dataWrite_out);
    bar_ex_mem.memToReg_out(ex_mem_memToReg_out);
    bar_ex_mem.ula_zero_out(ex_mem_ula_zero_out);
    bar_ex_mem.ula_negative_out(ex_mem_ula_negative_out);
    bar_ex_mem.flagSel_out(ex_mem_flagSel_out);
    bar_ex_mem.pc_out(ex_mem_pc_out);
    bar_ex_mem.ula_result_out(ex_mem_ula_result_out);
    bar_ex_mem.reg_data_out(ex_mem_reg_data_out);

    SC_THREAD(clock_gen);
    SC_THREAD(test);
  }
};

int sc_main(int argc, char **argv) {
  test_cpu tb("tb");
  sc_start();
  return 0;
}
