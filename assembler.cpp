#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <regex>

using namespace std;

ifstream file;
vector<string> asmCode;

// Declaracao de metodos
// ---------------------
int readFile(char *fname);
int binToDec(string bin);
string decToBin(int dec);
string getOpCode(string op);
string getFuncCode(string op);
string getRegCode(string reg);
string extend(string s,char c);
std::vector<std::string> split(std::string &s, std::string rgx_str);
string Itype(string operation);
// ---------------------

int readFile(char *fname) {
    string line;
    file.open(fname);
    if (!file.is_open()) {
        cout << "Error!" << endl;
        return 1;
    }
    while (getline(file, line))
        asmCode.push_back(line);
    return 0;
}

string getOpCode(string op) {
    if (op == "xori")  return "001110";
    if (op == "andi")  return "001100";
    if (op == "lui")   return "001111";
    if (op == "beq")   return "000100";
    if (op == "j")     return "000010";
    if (op == "bne")   return "000101";
    if (op == "lw")    return "100011";
    if (op == "addiu") return "001001";
    if (op == "sltiu") return "001011";
    if (op == "sw")    return "101011";
    return "000000";
}

string getFuncCode(string op) {
    if (op == "subu") return "100011";
    if (op == "or")   return "100101";
    if (op == "slt")  return "101010";
    if (op == "addu") return "100001";
    if (op == "sll")  return "000000";
    if (op == "srl")  return "000010";
}

string getRegCode(string reg) {
    if (reg == "$zero") return "00000";
    if (reg == "$v0") return "00010";
    if (reg == "$v1") return "00011";
    if (reg == "$a0") return "00100";
    if (reg == "$a1") return "00101";
    if (reg == "$a2") return "00110";
    if (reg == "$a3") return "00111";
    if (reg == "$t0") return "01000";
    if (reg == "$t1") return "01001";
    if (reg == "$t2") return "01010";
    if (reg == "$t3") return "01011";
    if (reg == "$t4") return "01100";
    if (reg == "$t5") return "01101";
    if (reg == "$t6") return "01110";
    if (reg == "$t7") return "01111";
    if (reg == "$t8") return "11000";
    if (reg == "$t9") return "11001";
    if (reg == "$s0") return "10000";
    if (reg == "$s1") return "10001";
    if (reg == "$s2") return "10010";
    if (reg == "$s3") return "10011";
    if (reg == "$s4") return "10100";
    if (reg == "$s5") return "10101";
    if (reg == "$s6") return "10110";
    if (reg == "$s7") return "10111";
    if (reg == "$gp") return "11100";
    if (reg == "$sp") return "11101";
    if (reg == "$fp") return "11110";
    if (reg == "$ra") return "11111";
}

string extend(string s,char c){
    int aux = 16 - s.length();
    s.insert(0,aux,c);
    return s;
}

std::vector<std::string> split(std::string &s, std::string rgx_str) {
    std::vector<std::string> v;
    std::regex rgx(rgx_str);
    std::sregex_token_iterator it(s.begin(), s.end(), rgx, -1);
    std::sregex_token_iterator end;
    while (it != end) {
        if((*it).compare(""))
            v.push_back(*it);
        it++;
    }
    return v;
}



int binToDec(string bin) {
    int result = 0;
    for (int i = 0; i < bin.size(); i++) {
        if (bin[i] == 0x31) {
            result += pow(2, bin.size() - i - 1);
        }
    }
    return result;
}

string decToBin(int dec) {
    bool baux = false;
    string aux;
    string res;
    int rem;
    int decn = dec;
    if(decn < 0) decn *= -1;
    while (decn > 0) {
        rem = decn % 2;
        decn = decn / 2;
        aux += 0x30 + rem;
    }
    if(dec < 0){
        for(int i = 0;i < aux.size();i++){
            if(baux == true)
                aux[i] = ((aux[i] == '0') ? '1' : '0');
            else if(aux[i] == '1')
                baux = true;
        }
        res = extend(string(aux.rbegin(), aux.rend()), '1');
    }else{
        res = extend(string(aux.rbegin(), aux.rend()), '0');
    }
    return res;
}

int searchLine(string s){
    for(int i = 0;i < asmCode.size();i++){
        if(asmCode[i].find(s) != string::npos)
            return i;
    }
    return -1;
}

string Itype(string operation) {//substituir operation por numero da linha em asmCode?
    vector<string> v = split(operation, "(\\s|,)+"); //     \\s e espaco em branco       | e um or (ou)       , e uma virgula
    string opcode = getOpCode(v[0]);
    string rs = getRegCode(v[2]);
    string rt = getRegCode(v[1]);
    string imm;
    if(!isalpha(v[3][0])){
        imm = decToBin(atoi(v[3].c_str()));
    }else{
        string label = v[3];
        int labelLine = searchLine(label);
    }
    return (opcode+rs+rt+imm);
}

string binToHex(string bin){
    string resp;
    for(int i = 0;i <= bin.length()-4;i+=4){
        string aux(bin,i,4);
        int vrau = binToDec(aux);
        if(vrau > 9){
            vrau += 0x37;
        }else{
            vrau += 0x30;
        }
        resp += vrau;
    }
    return resp;
}

int main(int argc, char **argv) {
    string s = "110110110101";
    cout << binToHex(s) << endl;
    return 0;
}
