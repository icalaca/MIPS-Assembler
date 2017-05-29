/*
 * Autores: Annderson Packeiser Oreto e Ian Oliveira Calaça da Costa
 */

#include "HelpFuncts.h"
#include "AsmFuncts.h"
#include <regex>

using namespace std;

/*
 * Metodo que conta a quantidade de operacoes do inicio ate uma label recebida por parametro.
 */
int HelpFuncts::countOpLabel(string label){
    int acm = 0;
    for(int i = 0;i < AsmFuncts::inpCode.size();i++){
        if(AsmFuncts::inpCode[i].find(label+":") != string::npos)
            return acm;
        if((AsmFuncts::inpCode[i].find(":") == string::npos) && (AsmFuncts::inpCode[i].find(".") == string::npos)){
            acm++;
        }
    }
    return -1;
}

/*
 * Metodo que conta a quantidade de operacoes do inicio ate uma linha
 * recebida por parametro para efetuar calculos do jump e adicoes de branch.
 */
int HelpFuncts::countOpLine(int line){
    int acm = 0;
    for(int i = 0;i <= line;i++){
        if((AsmFuncts::inpCode[i].find(":") == string::npos) && (AsmFuncts::inpCode[i].find(".") == string::npos)){
            acm++;
        }
    }
    return acm;
}

/*
 * Metodo que cria um vetor com substrings da string de entrada,
 * separando a mesma pela expressao regular recebida, tambem por parametro.
 */
vector<string> HelpFuncts::split(string &s, string rgx_str) {
    vector<string> v;
    regex rgx(rgx_str);
    sregex_token_iterator end;
    sregex_token_iterator it(s.begin(), s.end(), rgx, -1);
    while (it != end) {
        if((*it).compare(""))
            v.push_back(*it);
        it++;
    }
    return v;
}