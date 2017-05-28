//
// Created by dw on 28/05/17.
//

#include "HelpFuncts.h"
#include "AsmFuncts.h"
#include <regex>

using namespace std;

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

int HelpFuncts::countOpLine(int line){
    int acm = 0;
    for(int i = 0;i <= line;i++){
        if((AsmFuncts::inpCode[i].find(":") == string::npos) && (AsmFuncts::inpCode[i].find(".") == string::npos)){
            acm++;
        }
    }
    return acm;
}

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