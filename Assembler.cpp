#include <algorithm>
#include <regex>
#include <iostream>
#include "Conversion.h"
#include "HelpFuncts.h"
#include "Assembler.h"


using namespace std;

int Assembler::mainLine = 0;

string Assembler::iType(string operation, int line) {
    vector<string> v = HelpFuncts::split(operation, "(\\s|,)+"); //     \\s e espaco em branco       | e um or (ou)       , e uma virgula
    string opcode = AsmFuncts::getOpCode(v[0]);
    string rt = AsmFuncts::getRegCode(v[1]);
    string rs;
    string imm;
    if((v[0] == "sw") || (v[0] == "lw")){
        vector<string> aux = HelpFuncts::split(v[2],"(\\(|\\))+");
        rs = AsmFuncts::getRegCode(aux[1]);
        imm = Conversion::decToBin(stoi(aux[0]),16);
    }else if(v[0] == "lui"){
        rs = Conversion::decToBin(0,5);
        imm = Conversion::decToBin(stoi(v[2]),16);
    }else if((v[0] == "bne")||(v[0] == "beq")){
        rs = AsmFuncts::getRegCode(v[1]);
        rt = AsmFuncts::getRegCode(v[2]);
        string label = v[3];
        imm = Conversion::decToBin(HelpFuncts::countOpLabel(label) - HelpFuncts::countOpLine(line),16);
    }else{
        rs = AsmFuncts::getRegCode(v[2]);
        imm = Conversion::decToBin(stoi(v[3]),16);
    }
    return (opcode+rs+rt+imm);
}

string Assembler::jType(string operation,int line){
    vector<string> v = HelpFuncts::split(operation,"(\\s)+");
    string opcode = AsmFuncts::getOpCode(v[0]);
    string label = v[1];
    int addr = BASE + 4*HelpFuncts::countOpLabel(label);
    return (opcode+Conversion::decToBin(addr,28));
}

string Assembler::rType(string operation, int line){
    vector<string> v = HelpFuncts::split(operation,"(\\s|,)+");
    string opcode = AsmFuncts::getOpCode(v[0]);
    string rs,rd,rt,shift,func;
    if((v[0] == "sll") || (v[0] == "srl")){
        rs = Conversion::decToBin(0,5);
        rt = AsmFuncts::getRegCode(v[2]);
        rd = AsmFuncts::getRegCode(v[1]);
        shift = Conversion::decToBin(stoi(v[3]),5);
        func = AsmFuncts::getFuncCode(v[0]);
    }else{
        rs = AsmFuncts::getRegCode(v[2]);
        rt = AsmFuncts::getRegCode(v[3]);
        rd = AsmFuncts::getRegCode(v[1]);
        shift = Conversion::decToBin(0,5);
        func = AsmFuncts::getFuncCode(v[0]);
    }
    return (opcode + rs + rt + rd + shift + func);
}


string Assembler::procInst(string inst, int line){
    string resp = "";
    vector<string> minst = HelpFuncts::split(inst,"(\\s)+");
    if(AsmFuncts::getType(minst[0]) == TYPE_I){
        resp = iType(inst, line);
    }
    if(AsmFuncts::getType(minst[0]) == TYPE_R){
        resp = rType(inst, line);
    }
    if(AsmFuncts::getType(minst[0]) == TYPE_J){
        resp = jType(inst, line);
    }
    return Conversion::binToHex(resp);
}

void Assembler::procAsmLine(string line, int n){
    vector<string> mline = HelpFuncts::split(line,"(\\s)+");
    if((mline[0] == ".text") || (mline[0].find(':') != string::npos))
        return;
    if(mline[0] == ".globl") {
        mainLine = HelpFuncts::countOpLabel(mline[1]);
        return;
    }
    AsmFuncts::outCode.push_back("0x"+procInst(line, n));
}

void Assembler::buildObj(void){
    for(int i = 0;i < AsmFuncts::inpCode.size();i++) {
        Assembler::procAsmLine(AsmFuncts::inpCode[i], i);
    }
    string bin = Conversion::decToBin(Assembler::mainLine,32);
    AsmFuncts::outCode.push_back("0x"+Conversion::binToHex(bin));
}