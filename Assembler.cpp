/*
 * Autores: Annderson Packeiser Oreto e Ian Oliveira Calaça da Costa
 */

#include <algorithm>
#include <regex>
#include <iostream>
#include "Conversion.h"
#include "HelpFuncts.h"
#include "Assembler.h"


using namespace std;

// numero da linha onde a label da diretiva globl esta localizada.
int Assembler::mainLine = 0;

/*
 * Metodo que monta o codigo em assembly de uma instrucao do tipo I,
 * recebida como codigo binario por parametro.
 */
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

/*
 * Metodo que monta o codigo em assembly de uma instrucao do tipo J,
 * recebida como codigo binario por parametro.
 */
string Assembler::jType(string operation,int line){
    vector<string> v = HelpFuncts::split(operation,"(\\s)+");
    string opcode = AsmFuncts::getOpCode(v[0]);
    string label = v[1];
    int addr = BASE + 4*HelpFuncts::countOpLabel(label);
    return (opcode+Conversion::decToBin(addr,28));
}

/*
 * Metodo que monta o codigo em assembly de uma instrucao do tipo R,
 * recebida como codigo binario por parametro.
 */
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

/*
 * Metodo que recebe uma instrucao e filtra nele
 * qual o tipo da instrucao a ser tratada, enviando a mesma ao metodo adequado.
 */
string Assembler::procInst(string inst, int line){
    string resp = "";
    vector<string> minst = HelpFuncts::split(inst,"(\\s)+"); // quebra por espaco apenas a primeira instrucao para teste.
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

/*
 * Metodo que processa uma linha do arquivo de entrada para montagem e
 * adiciona a instrucao montada ao arquivo de saida.
 */
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

/*
 * Metodo que processa em um laco todas as linhas do arquivo de entrada para montagem.
 */
void Assembler::buildObj(void){
    for(int i = 0;i < AsmFuncts::inpCode.size();i++) {
        Assembler::procAsmLine(AsmFuncts::inpCode[i], i);
    }
    string bin = Conversion::decToBin(Assembler::mainLine,32);
    AsmFuncts::outCode.push_back("0x"+Conversion::binToHex(bin));
}