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

int main(int argc, char* argv[]) {
    ifstream file(argv[1]);

    string token;
    bool isData = true;
    bool isAddress = true;
    while(getline(file, token)) {
       if(token == "--") {
            isData = false;
            continue;
       }

       std::istringstream iss(token);

       if(isData) {
        int address, value;
        iss >> address >> value;
       } else {
        std::string instruc;
        iss >> instruc;


        if(is_logical_instruction(instruc)) {
            uint rs, rt, rd;
            iss >> rs >> rt >> rd;
            cout << "Palavra: 0b" << bitset<6>{0b010000} << bitset<5>{rd} << bitset<5>{rs} << bitset<5>{rt} << bitset<11>{get_funct(instruc)} << endl;
        } else if (is_jump_instruction(instruc)) {
            uint immediate;
            iss >> immediate;
            cout << "Palavra: 0b" << bitset<6>{0b110000} << bitset<26>{immediate} << endl;
        } else {
            int rs, rt, immediate;
            iss >> rs >> rt >> immediate;
            cout << "Palavra: 0b" << bitset<6>{0b100000} << bitset<5>{rs} << bitset<5>{rt} << bitset<16>{immediate} << endl;
        }
       }



        cout << token << endl;
    }
}