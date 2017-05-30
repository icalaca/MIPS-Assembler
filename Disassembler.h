//
// Created by dw on 28/05/17.
//
#include <string>
#include "HelpFuncts.h"

#ifndef TRABALHO_OAC_DISASSEMBLER_H
#define TRABALHO_OAC_DISASSEMBLER_H
class Disassembler{
public:
    static void procObjLine(std::string line, int n);
    static void addLabel(int line, std::string label);
    static int labelCount;
    static void putLabels();
    static void buildCode(void);
    static std::vector<std::pair<int, std::string>> labels;
private:
    //static std::vector<std::pair<int, std::string>> labels;
    static std::string iType(std::string bin, int line);
    static std::string jType(std::string bin);
    static std::string rType(std::string bin);
    static std::string procObj(std::string hex, int line);
    static bool labelExists(int line);
    static std::string getLabel(int line);
};
#endif //TRABALHO_OAC_DISASSEMBLER_H
