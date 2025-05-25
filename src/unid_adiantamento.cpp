#include "../include/unid_adiantamento.hpp"

// 2 -> EX_MEM
// 1 -> MEM_WB
// 0 -> sem adiantamento
void unid_adiantamento::computar_adiantamento(){ 
     if (EX_MEM_RegWrite.read() &&
         EX_MEM_rd.read() != 0 &&
         EX_MEM_rd.read() == ID_EX_rs.read()) {
         ForwardA.write(2); 
     } else if (MEM_WB_RegWrite.read() &&
                MEM_WB_rd.read() != 0 &&
                MEM_WB_rd.read() == ID_EX_rs.read()) {
         ForwardA.write(1); 
     } else {
        ForwardA.write(0);
     }
 
     if (EX_MEM_RegWrite.read() &&
         EX_MEM_rd.read() != 0 &&
         EX_MEM_rd.read() == ID_EX_rt.read()) {
         ForwardB.write(2); 
     } else if (MEM_WB_RegWrite.read() &&
                MEM_WB_rd.read() != 0 &&
                MEM_WB_rd.read() == ID_EX_rt.read()) {
         ForwardB.write(1); 
     } else {
        ForwardB.write(0);
     }
}