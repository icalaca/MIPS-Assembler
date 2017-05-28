#include <string>

#ifndef TRABALHO_OAC_CONVERSION_H
#define TRABALHO_OAC_CONVERSION_H
class Conversion {
public:
    static int binToDec(std::string bin);

    static std::string decToBin(int dec, int ext);

    static std::string binToHex(std::string bin);

    static std::string hexToBin(std::string hex);
};
#endif
