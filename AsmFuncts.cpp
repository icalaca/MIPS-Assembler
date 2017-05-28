#include "AsmFuncts.h"

using namespace std;
vector<string> AsmFuncts::inpCode, AsmFuncts::outCode;

string AsmFuncts::getOpCode(string op) {
    for (int i = 0; i < Codes::typeIOp.size(); i++) {
        if(op == Codes::typeIOp[i].first)
            return Codes::typeIOp[i].second;
        if(op == Codes::typeIOp[i].second)
            return Codes::typeIOp[i].first;
    }
    for (int i = 0; i < Codes::typeJOp.size(); i++) {
        if(op == Codes::typeJOp[i].first)
            return Codes::typeJOp[i].second;
        if(op == Codes::typeJOp[i].second)
            return Codes::typeJOp[i].first;
    }
    return "000000";
}

string AsmFuncts::getFuncCode(string op) {
    for (int i = 0; i < Codes::typeROp.size(); i++) {
        if(op == Codes::typeROp[i].second)
            return Codes::typeROp[i].first;
        if(op == Codes::typeROp[i].first)
            return Codes::typeROp[i].second;
    }
    return "000000";
}

string AsmFuncts::getRegCode(string reg) {
    for(int i = 0;i < Codes::Regs.size();i++){
        if(reg == Codes::Regs[i].first)
            return Codes::Regs[i].second;
        if(reg == Codes::Regs[i].second)
            return Codes::Regs[i].first;
    }
    return "";
}

int AsmFuncts::getType(string op){
    if(op == Conversion::decToBin(0,6))
        return TYPE_R;
    for (int i = 0; i < Codes::typeROp.size(); i++)
        if((op == Codes::typeROp[i].first))
            return TYPE_R;

    for (int i = 0; i < Codes::typeIOp.size(); i++)
        if((op == Codes::typeIOp[i].first) || (op == Codes::typeIOp[i].second))
            return TYPE_I;

    for (int i = 0; i < Codes::typeJOp.size(); i++)
        if((op == Codes::typeJOp[i].first) || (op == Codes::typeJOp[i].second))
            return TYPE_J;
    return -1;
}
