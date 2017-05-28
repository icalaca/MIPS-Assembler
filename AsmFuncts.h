//
// Created by dw on 28/05/17.
//
#include "Codes.h"
#include <vector>
#include "Conversion.h"

#ifndef TRABALHO_OAC_ASM_FUNCTS_H
#define TRABALHO_OAC_ASM_FUNCTS_H
#define BASE 0x00400000
#define TYPE_R 1
#define TYPE_I 2
#define TYPE_J 3

class AsmFuncts {
public:
    static std::vector<std::string> inpCode, outCode;

    static int getType(std::string op);

    static std::string getRegCode(std::string reg);

    static std::string getOpCode(std::string op);

    static std::string getFuncCode(std::string op);
};

#endif //TRABALHO_OAC_ASM_FUNCTS_H
