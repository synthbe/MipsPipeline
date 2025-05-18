#ifndef UNID_DETEC_CONFLITOS_HPP
#define UNID_DETEC_CONFLITOS_HPP

#include <systemc.h>
SC_MODULE(unid_detec_conflitos) {
    sc_in<sc_uint<5>> IF_ID_rs;
    sc_in<sc_uint<5>> IF_ID_rt;
    sc_in<sc_uint<5>> ID_EX_rt;
    sc_in<bool>       ID_EX_MemRead;

    sc_out<bool> PCWrite;
    sc_out<bool> IF_ID_Write;
    sc_out<bool> ControlMux;

    void detec_conflito();

    SC_CTOR(unid_detec_conflitos) {
        SC_METHOD(detec_conflito);
        sensitive << IF_ID_rs << IF_ID_rt
                  << ID_EX_rt << ID_EX_MemRead;
    }
};
#endif // !UNID_DETEC_CONFLITOS_HPP