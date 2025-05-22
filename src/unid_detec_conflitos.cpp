#include "../include/unid_detec_conflitos.hpp"

void unid_detec_conflitos::detec_conflito() {
    if (ID_EX_MemRead.read() &&
        (ID_EX_rt.read() == IF_ID_rs.read() || ID_EX_rt.read() == IF_ID_rt.read())) {
        PCWrite.write(false);
        IF_ID_Write.write(false);
        ControlMux.write(true);
    } else {
        PCWrite.write(true);
        IF_ID_Write.write(true);
        ControlMux.write(false); 
    }
}
