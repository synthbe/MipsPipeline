#ifndef UNID_ADIANTAMENTO_HPP
#define UNID_ADIANTAMENTO_HPP

#include <systemc.h>

SC_MODULE(unid_adiantamento) {
    sc_in<sc_uint<5>> ID_EX_rs;
    sc_in<sc_uint<5>> ID_EX_rt;
    sc_in<sc_uint<5>> EX_MEM_rd;
    sc_in<bool>       EX_MEM_RegWrite;
    sc_in<sc_uint<5>> MEM_WB_rd;
    sc_in<bool>       MEM_WB_RegWrite;

    sc_out<sc_uint<2>> ForwardA;
    sc_out<sc_uint<2>> ForwardB;

    void computar_adiantamento();

    SC_CTOR(unid_adiantamento){
        SC_METHOD(computar_adiantamento);
        sensitive << ID_EX_rs << ID_EX_rt
                  << EX_MEM_rd << EX_MEM_RegWrite
                  << MEM_WB_rd << MEM_WB_RegWrite;
    }
};

#endif // !UNID_ADIANTAMENTO_HPP