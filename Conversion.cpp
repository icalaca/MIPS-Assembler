#include "Conversion.h"
#include "math.h"

using namespace std;

string extend(string s,char c,int ext){
    int aux = ext - s.length();
    s.insert(0,aux,c);
    return s;
}

int Conversion::binToDec(string bin) {
    bool baux = false;
    int result = 0;
    if(bin[0] == 1){
        for(int i = bin.size()-1;i >= 0;i--){
            if(baux == true)
                bin[i] = ((bin[i] == '0') ? '1' : '0');
            else if(bin[i] == '1')
                baux = true;
        }
    }
    for (int i = 0; i < bin.size(); i++) {
        if (bin[i] == 0x31)
            result += pow(2, bin.size() - i - 1);
    }
    return (baux) ? result*-1 : result;
}

string Conversion::decToBin(int dec,int ext) {
    bool baux = false;
    string aux;
    string res;
    int rem;
    int decn = dec;
    if(decn < 0) decn *= -1;
    while (decn > 0) {
        rem = decn % 2;
        decn = decn / 2;
        aux += 0x30 + rem;
    }
    if(dec < 0){
        for(int i = 0;i < aux.size();i++){
            if(baux == true)
                aux[i] = ((aux[i] == '0') ? '1' : '0');
            else if(aux[i] == '1')
                baux = true;
        }
        res = extend(string(aux.rbegin(), aux.rend()), '1',ext);
    }else{
        res = extend(string(aux.rbegin(), aux.rend()), '0',ext);
    }
    return res;
}

string Conversion::binToHex(string bin){
    string resp;
    for(int i = 0;i <= bin.length()-4;i+=4){
        string aux(bin,i,4);
        int vrau = binToDec(aux);
        if(vrau > 9){
            vrau += 0x37;
        }else{
            vrau += 0x30;
        }
        resp += vrau;
    }
    return resp;
}

string Conversion::hexToBin(string hex){
    string resp;
    for(int i = 0; i < hex.length(); i++){
        if(!isalpha(hex[i])){
            resp += decToBin(hex[i]-0x30,4);
        }else{
            resp += decToBin(hex[i] - 0x37,4);
        }
    }
    return resp;
}