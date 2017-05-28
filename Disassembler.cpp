#include "Disassembler.h"
#include "Assembler.h"
#include <iostream>


using namespace std;

int Disassembler::labelCount = 0;
vector<pair<int, string>> Disassembler::labels;

string Disassembler::iType(string bin, int line){
    string op = AsmFuncts::getOpCode(bin.substr(0,6));
    string rs = AsmFuncts::getRegCode(bin.substr(6,5));
    string rt = AsmFuncts::getRegCode(bin.substr(11,5));
    string imm = std::to_string(Conversion::binToDec(bin.substr(16,16)));
    if((op == "sw") || (op == "lw")){
        return (op + " " + rt + ", " + imm + "(" + rs + ")");
    }
    if(op == "lui"){
        return (op + " " + rt + ", " + imm);
    }
    if((op == "bne")||(op == "beq")){
        string label = "LABEL_"+to_string(labelCount);
        int l = line + stoi(imm) + 1;
        addLabel(l,label);
        return (op + " " + rs + ", " + rt + ", "+label);
    }
    return (op + " " + rt + ", " + rs + ", " + imm);
}

string Disassembler::jType(string bin){
    string op = AsmFuncts::getOpCode(bin.substr(0,6));
    string label = "LABEL_"+to_string(labelCount);
    int addr = Conversion::binToDec(bin.substr(6,26));
    addr <<= 2;
    int line = (addr-BASE)/4;
    addLabel(line,label);
    return (op+" "+label);
}

string Disassembler::rType(string bin){
    string op = AsmFuncts::getOpCode(bin.substr(0,6));
    string rs,rt,rd,shift,func;
    rs = AsmFuncts::getRegCode(bin.substr(6,5));
    rt = AsmFuncts::getRegCode(bin.substr(11,5));
    rd = AsmFuncts::getRegCode(bin.substr(16,5));
    func = AsmFuncts::getFuncCode(bin.substr(26,6));
    if((func == "sll") || (func == "srl")){   //opcode == 000000
        shift = to_string(Conversion::binToDec(bin.substr(21,5)));
        return (func+" "+rd+", "+rt+", "+shift);
    }
    return (func+" "+rd+", "+rs+", "+rt);
}

string Disassembler::procObj(string hex, int line){
    string bin = Conversion::hexToBin(hex);
    string aux = bin.substr(0,6);
    string resp;
    if(AsmFuncts::getType(aux) == TYPE_I){
        resp = iType(bin, line);
        return resp;
    }
    if(AsmFuncts::getType(aux) == TYPE_R){
        resp = rType(bin);
        return resp;
    }
    if(AsmFuncts::getType(aux) == TYPE_J){
        resp = jType(bin);
        return resp;
    }
    return "";
}

void Disassembler::procObjLine(string line, int n){
    vector<string> mline = HelpFuncts::split(line,"(x)");
    if(n == -1){//indica ultima linha
        int line = Conversion::binToDec(Conversion::hexToBin(mline[1]));
        addLabel(line,"main");
        return;
    }
    AsmFuncts::outCode.push_back("\t" + procObj(mline[1], n));
}

void Disassembler::putLabels(){
    if(!labels.empty()){
        for(int i = 0;i < labels.size();i++)
            AsmFuncts::outCode[labels[i].first].insert(0,labels[i].second+":\n");
    }
}


void Disassembler::addLabel(int line, string label){
    if(label == "main"){
        for(int i = 0;i < labels.size();i++)
            if(labels[i].first == line+2){
                string mlabel = labels[i].second;
                AsmFuncts::outCode[1].insert(AsmFuncts::outCode[1].length(),mlabel);
                return;
            }
        AsmFuncts::outCode[1].insert(AsmFuncts::outCode[1].length(),label);
    }
    labels.push_back(mp(line+2,label));//+2 => .text e .globl
    labelCount++;
}

void Disassembler::buildCode(void){
    AsmFuncts::outCode.push_back(".text");
    AsmFuncts::outCode.push_back(".globl ");
    for(int i = 0;i < AsmFuncts::inpCode.size();i++) {
        if(i == AsmFuncts::inpCode.size() - 1)
            Disassembler::procObjLine(AsmFuncts::inpCode[i], -1);
        else
            Disassembler::procObjLine(AsmFuncts::inpCode[i], i);
    }
    Disassembler::putLabels();

}