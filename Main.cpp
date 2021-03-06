/*
 * Autores: Annderson Packeiser Oreto e Ian Oliveira Calaça da Costa
 */

#include <iostream>
#include <fstream>
#include <string.h>
#include "Assembler.h"
#include "Disassembler.h"


using namespace std;

void printAscii(void){
    cout << "    _______        _        __              " << endl;
    cout << "   |__   __|      | |      /_ |             " << endl;
    cout << "      | |_ __ __ _| |__     | |             " << endl;
    cout << "      | | '__/ _` | '_ \\    | |             " << endl;
    cout << "      | | | | (_| | |_) |   | |             " << endl;
    cout << "   ___|_|_|  \\__,_|_.__(_)  |_|             " << endl;
    cout << "  / __ \\                  /\\                " << endl;
    cout << " | |  | |_ __ __ _       /  \\   _ __ __ _   " << endl;
    cout << " | |  | | '__/ _` |     / /\\ \\ | '__/ _` |  " << endl;
    cout << " | |__| | | | (_| |_   / ____ \\| | | (_| |_ " << endl;
    cout << "  \\____/|_|  \\__, (_) /_/    \\_\\_|  \\__, (_)" << endl;
    cout << "              __/ | Ian O.C.C          | |  " << endl;
    cout << "             |___/    Annderson O.     |_|  " << endl;
    cout << endl;
}

/*
 * O metodo imprime na tela a instrucao para uso do programa.
 */
void printHelp(char *exName){
    cout << "Assembler:\n" << exName << " --asm arquivo\n";
    cout << "Disassembler:\n" << exName << " --disasm arquivo\n";
}

/*
 * O metodo le o arquivo para assemblar ou desassemblar e o carrega em um vetor de string.
 */
int readFile(char *fname) {
    ifstream ifile;
    string line;
    ifile.open(fname);
    if (!ifile.is_open()) {
        cout << "Erro na leitura do arquivo." << endl;
        return 1;
    }
    while (getline(ifile, line))
        if(line != "")
            AsmFuncts::inpCode.push_back(line);
    return 0;
}

/*
 * Escreve em um arquivo de saida as instrucoes convertidas que estao contidas no vetor de string outCode.
 */
int writeFile(char *fname){
    ofstream ofile;
    ofile.open(fname);
    if (!ofile.is_open()) {
        cout << "Erro na criacao do arquivo." << endl;
        return 1;
    }
    for(int i = 0;i < AsmFuncts::outCode.size();i++)
        ofile << AsmFuncts::outCode[i]+"\n";
    ofile.close();
    return 0;
}

/*
 * Metodo principal que recebe os parametros enviado por linha de comando para a montagem ou desmontagem do codigo.
 */
int main(int argc, char **argv) {
    printAscii();
    if(argc != 3) {
        printHelp(argv[0]);
        return 0;
    }
    readFile(argv[2]);
    if(strcmp(argv[1],"--asm") == 0) {
        Assembler::buildObj();
        if(writeFile((char *)"obj.txt") == 0)
            cout << "Arquivo obj.txt gerado!" << endl;
    }
    if(strcmp(argv[1],"--disasm") == 0) {
        Disassembler::buildCode();
        if(writeFile((char *)"code.asm") == 0)
            cout << "Arquivo code.asm gerado!" << endl;
    }
    return 0;
}