//
// Created by dw on 28/05/17.
//

#include "Codes.h"

using namespace std;
vector<pair<string, string>> Codes::Regs =
        {mp("$zero", "00000"), mp("$v0", "00010"), mp("$v1", "00011"),
         mp("$a0", "00100"), mp("$a1", "00101"), mp("$a2", "00110"),
         mp("$a3", "00111"), mp("$t0", "01000"), mp("$t1", "01001"),
         mp("$t2", "01010"), mp("$t3", "01011"), mp("$t4", "01100"),
         mp("$t5", "01101"), mp("$t6", "01110"), mp("$t7", "01111"),
         mp("$t8", "11000"), mp("$t9", "11001"), mp("$s0", "10000"),
         mp("$s1", "10001"), mp("$s2", "10010"), mp("$s3", "10011"),
         mp("$s4", "10100"), mp("$s5", "10101"), mp("$s6", "10110"),
         mp("$s7", "10111"), mp("$gp", "11100"), mp("$sp", "11101"),
         mp("$fp", "11110"), mp("$ra", "11111")};

vector<pair<string, string>> Codes::typeJOp = {mp("j", "000010")};

vector<pair<string, string>> Codes::typeROp =
        {mp("subu", "100011"), mp("or", "100101"), mp("slt", "101010"),
         mp("addu", "100001"), mp("sll", "000000"), mp("srl", "000010")};

vector<pair<string, string>> Codes::typeIOp =
        {mp("xori", "001110"), mp("lui", "001111"), mp("andi", "001100"),
         mp("addiu", "001001"), mp("sltiu", "001011"), mp("beq", "000100"),
         mp("bne", "000101"), mp("lw", "100011"), mp("sw", "101011")};