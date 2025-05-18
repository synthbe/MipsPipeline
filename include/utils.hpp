#ifndef UTILS_HPP
#define UTILS_HPP

#include <systemc.h>


// Permite que escrevamos literais binários usando _ para separar as seções dos bits
const int TAMANHO = 32; 
sc_uint<TAMANHO> operator""_u32(const char* str, std::size_t len) {
    sc_uint<TAMANHO> result = 0;
    int bit_pos = 0;

    for (int i = len - 1; i >= 0; --i) {
        char c = str[i];
        if (c == '_') continue;

        if (c == '1' || c == '0') {
            if (bit_pos >= TAMANHO) break;
            result[bit_pos++] = (c == '1') ? 1 : 0;
        } else {
            throw std::runtime_error("Invalid binary digit in literal");
        }
    }

    return result;
}

#endif