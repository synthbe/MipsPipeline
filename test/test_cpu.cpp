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
#include "../include/mem_dados.hpp"
#include "../include/mux4.hpp"
#include "../include/pc_end.hpp"
#include "../include/and.hpp"
#include "../include/utils.hpp"
#include "../include/mem_wb.hpp"

#include <bitset>
#include <systemc.h>

SC_MODULE(test_cpu) {
  const int CLOCK_SIZE_NS = 20;
  sc_signal<bool> clk;
  sc_signal<bool> vcc, earth;

  // Primeiro estágio
  registrador<32> pc{"pc"};
  mem_instrucao mem_ins{"mem_ins"};
  somador inc{"inc"};
  sc_signal<sc_uint<32>> fourConstant, pcCurrValue, palavra;
  sc_signal<sc_uint<32>> inc_result_out;
  sc_signal<bool> resetPc, pcWrite;

  // Registradores IF/ID
  if_id bar_if_id{"bar_if_id"};
    sc_signal<sc_uint<32>> ifid_pc_saida, ifid_inst_saida;
    sc_signal<sc_uint<5>> read1, read2, write1;
    sc_signal<sc_int<16>> immediate;
    sc_signal<sc_uint<26>> absolute;


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
    sc_signal<sc_uint<26>> id_ex_absolute_out;

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
  sc_signal<sc_uint<26>> ex_mem_absolute_out;
  sc_signal<sc_uint<5>> ex_mem_rd_out;

  // Quarto estágio
  mem_dados mem_mem_dados{"mem_mem_dados"};
  mux4<bool> mux_flag_sel{"mux_flag_sel"};
  pc_end mem_pc_end{"mem_pc_end"};
  and_port jump_gate{"gate_gate"};
  mux2<sc_uint<32>> mux_pc_next_value{"mux_pc_next_value"};

  sc_signal<sc_int<32>> mem_dados_result_out;
  sc_signal<sc_uint<32>> pc_end_result_out;
  sc_signal<bool> mux_flag_sel_out;
  sc_signal<bool> jump_gate_out;
  sc_signal<sc_uint<32>> pc_next_value_out;

  // Quinto estágio
  mem_wb bar_mem_wb{"bar_mem_wb"};
  mux2<sc_int<32>> mux_mem_to_reg{"mux_mem_to_reg"};
 
    sc_signal<bool> mem_wb_regWrite_out, mem_wb_memToReg_out;
    sc_signal<sc_uint<5>> mem_wb_rd_out;
    sc_signal<sc_int<32>> mem_wb_ula_result_out, mem_wb_mem_data_out;
    sc_signal<sc_int<32>> mux_mem_to_reg_out;

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
    mem_ins.mem[4] = 0b11000000; // Jump incondicional
    mem_ins.mem[5] = 0b0;
    mem_ins.mem[6] = 0b0;
    mem_ins.mem[7] = 0b00000100;

    for(int i=0; i<6; i++) {
        wait(CLOCK_SIZE_NS, SC_NS);
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "palavra lida: 0b" << std::bitset<32>{palavra.read()} << std::endl;
        std::cout << "palavra: 0b" <<  std::bitset<32>{ifid_inst_saida.read()} << std::endl; 
        std::cout << "isJump controle: " << isJump.read() << std::endl;
        std::cout << "isJump (id/ex): " << id_ex_isJump_out.read() << std::endl;
        std::cout << "isJump (ex/mem): " << ex_mem_isJump_out.read() << std::endl;
        std::cout << "endereco: " << std::hex << "0x" << pc_end_result_out.read() << std::endl;
        std::cout << "Jump gate: " << jump_gate_out.read() << std::endl;
        std::cout << "Last last last program counter: " << std::hex << "0x" << ex_mem_pc_out.read() << std::endl;
        std::cout << "Last last program counter: " << std::hex << "0x" << id_ex_pc_out.read() << std::endl;
        std::cout << "Last program counter: " << std::hex << "0x" << ifid_pc_saida.read() << std::endl;
        std::cout << "Curr program counter: " << std::hex << "0x" << pc.d_out.read() << std::endl;
        std::cout << "----------------------------------------" << std::endl;
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
    pc.d_in(pc_next_value_out);
    pc.d_out(pcCurrValue);

    inc.a(pc.d_out);
    inc.b(fourConstant);
    inc.d_out(inc_result_out);

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
    bar_if_id.absolute(absolute);

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
    b_reg.rd(mem_wb_rd_out);
    b_reg.wd(mux_mem_to_reg_out);
    b_reg.rd1(b_reg_result1);
    b_reg.rd2(b_reg_result2);

    bar_id_ex.clk(clk);
    bar_id_ex.rst(jump_gate_out);
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
    bar_id_ex.absolute(absolute);

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
    bar_id_ex.absolute_out(id_ex_absolute_out);

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
    bar_ex_mem.absolute(id_ex_absolute_out);

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
    bar_ex_mem.absolute_out(ex_mem_absolute_out);
    bar_ex_mem.rd(id_ex_rd_out);
    bar_ex_mem.rd_out(ex_mem_rd_out);

    mem_mem_dados.clk(clk);
    mem_mem_dados.dataRead(ex_mem_dataRead_out);
    mem_mem_dados.dataWrite(ex_mem_dataWrite_out);
    mem_mem_dados.endereco(ex_mem_ula_result_out);
    mem_mem_dados.dados(ex_mem_reg_data_out);
    mem_mem_dados.resposta(mem_dados_result_out);

    mem_pc_end.pc(ex_mem_pc_out);
    mem_pc_end.absoluto(ex_mem_absolute_out);
    mem_pc_end.resposta(pc_end_result_out);

    mux_flag_sel.sel(ex_mem_flagSel_out);
    // ORDEM IMPORTA AQUI: consulte enum na parte de controle
    mux_flag_sel.A(vcc);
    mux_flag_sel.B(ex_mem_ula_zero_out);
    mux_flag_sel.C(ex_mem_ula_negative_out);
    mux_flag_sel.D(earth);
    mux_flag_sel.out(mux_flag_sel_out);

    jump_gate.A(ex_mem_isJump_out);
    jump_gate.B(mux_flag_sel_out);
    jump_gate.out(jump_gate_out);

    mux_pc_next_value.sel(jump_gate_out);
    mux_pc_next_value.A(inc_result_out);
    mux_pc_next_value.B(pc_end_result_out);
    mux_pc_next_value.out(pc_next_value_out);

    bar_mem_wb.clk(clk);
    bar_mem_wb.rst(earth);
    bar_mem_wb.earth(earth);
    bar_mem_wb.vcc(vcc);
    bar_mem_wb.regWrite(ex_mem_regWrite_out);
    bar_mem_wb.memToReg(ex_mem_memToReg_out);
    bar_mem_wb.ula_result(ex_mem_ula_result_out);
    bar_mem_wb.mem_data(mem_dados_result_out);
    bar_mem_wb.rd(ex_mem_rd_out);
    bar_mem_wb.regWrite_out(mem_wb_regWrite_out);
    bar_mem_wb.memToReg_out(mem_wb_memToReg_out);
    bar_mem_wb.ula_result_out(mem_wb_ula_result_out);
    bar_mem_wb.mem_data_out(mem_wb_mem_data_out);
    bar_mem_wb.rd_out(mem_wb_rd_out);

    mux_mem_to_reg.sel(mem_wb_memToReg_out);
    // ORDEM IMPORTA AQUI: consulte enum na parte de controle
    mux_mem_to_reg.A(mem_wb_ula_result_out);
    mux_mem_to_reg.B(mem_wb_mem_data_out);
    mux_mem_to_reg.out(mux_mem_to_reg_out);


    SC_THREAD(clock_gen);
    SC_THREAD(test);
  }
};

int sc_main(int argc, char **argv) {
  test_cpu tb("tb");
  sc_start();
  return 0;
}
