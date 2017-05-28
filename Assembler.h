//
// Created by dw on 28/05/17.
//
#include "AsmFuncts.h"
#include <string>

#ifndef TRABALHO_OAC_ASSEMBLER_H
#define TRABALHO_OAC_ASSEMBLER_H
class Assembler{
public:
    static void procAsmLine(std::string line, int n);
    static int mainLine;
    static void buildObj(void);

private:
    static std::string procInst(std::string inst, int line);
    static std::string rType(std::string operation, int line);
    static std::string jType(std::string operation,int line);
    static std::string iType(std::string operation, int line);
};
#endif //TRABALHO_OAC_ASSEMBLER_H
