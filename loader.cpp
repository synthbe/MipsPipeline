#include<fstream>
#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<bitset>
using namespace std;

vector<string> logical_instructions = {
    "and", "or", "xor", "not", "add", "sub"
};

vector<string> jump_instructions = {
    "j", "jz", "jn"
};

bool is_logical_instruction(const string& instruction) {
    for(const string &instr : logical_instructions) {
        if(instruction == instr) {
            return true;
        }
    }
    return false;
}

bool is_jump_instruction(const string& instruction) {
    for(const string &instr : jump_instructions) {
        if(instruction == instr) {
            return true;
        }
    }
    return false;
}

uint get_funct(string& instruction) {
    if(instruction == "add") return 0;
    if(instruction == "sub") return 1;
    if(instruction == "and") return 2;
    if(instruction == "or") return 3;
    if(instruction == "xor") return 4;
    if(instruction == "not") return 5;
    return -1;
}

string output = 
"#include \"../include/carregar.hpp\"\n"
"\n"
"void carregar(sc_uint<8> *mem_instrucao, sc_int<32> *mem_dados) {\n";

int main(int argc, char* argv[]) {
    ifstream file(argv[1]);

    string token;
    bool isData = true;
    bool isAddress = true;
    int offset = 0;
    while(getline(file, token)) {
        if(token == "--") {
            isData = false;
            continue;
        }

        std::istringstream iss(token);

        if(isData) {
            int address, value;
            iss >> address >> value;

            output.append("\tmem_dados[");
            output.append(to_string(address));
            output.append("] = ");
            output.append(to_string(value));
            output.append(";\n");
        } else {
            std::string instruc;
            iss >> instruc;

            string palavra;
            if(is_logical_instruction(instruc)) {
                uint rs, rt, rd;
                iss >> rs >> rt >> rd;
                palavra.append(bitset<6>{0b010000}.to_string());
                palavra.append(bitset<5>{rd}.to_string());
                palavra.append(bitset<5>{rs}.to_string());
                palavra.append(bitset<5>{rt}.to_string());
                palavra.append(bitset<11>{get_funct(instruc)}.to_string());
            } else if (is_jump_instruction(instruc)) {
                uint immediate;
                iss >> immediate;
                palavra.append(bitset<6>{0b110000}.to_string());
                palavra.append(bitset<26>{immediate}.to_string());
            } else {
                int rs, rt, immediate;
                iss >> rs >> rt >> immediate;
                palavra.append(bitset<6>{0b100000}.to_string());
                palavra.append(bitset<5>{rs}.to_string());
                palavra.append(bitset<5>{rt}.to_string());
                palavra.append(bitset<16>{immediate}.to_string());
            }

            for(int i=0; i<palavra.size(); i+=8) {
                string byte = palavra.substr(i, 8);
                bitset<8> b(byte);
                output.append("\tmem_instrucao[");
                output.append(to_string(offset + i/8));
                output.append("] = ");
                output.append("0b");
                output.append(b.to_string());
                output.append(";\n");
            }
            offset += 4;
        }
    }

    output.append("};\n");

    ofstream outFile("src/carregar.cpp");
    outFile << output;
    outFile.close();
    cout << "Arquivo test/carregar.cpp gerado com sucesso!" << endl;
}