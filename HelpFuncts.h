//
// Created by dw on 28/05/17.
//
#include <string>
#include <vector>

#ifndef TRABALHO_OAC_HELP_FUNCTS_H
#define TRABALHO_OAC_HELP_FUNCTS_H
class HelpFuncts {
public:
    static int countOpLine(int line);

    static int countOpLabel(std::string label);

    static std::vector<std::string> split(std::string &s, std::string rgx_str);
};
#endif //TRABALHO_OAC_HELP_FUNCTS_H
