/*
 * Autores: Annderson Packeiser Oreto e Ian Oliveira Calaça da Costa
 */

#include "Conversion.h"
#include "math.h"

using namespace std;

/*
 * O metodo adiciona o caractere "c" enviado por parametro "ext" vezes na frente da string "s".
 */
string extend(string s,char c,int ext){
    int aux = ext - s.length();
    s.insert(0,aux,c);
    return s;
}

/*
 * Este metodo converte um numero binario para um numero em decimal.
 */
int Conversion::binToDec(string bin) {
    bool baux = false;
    int result = 0;
    if(bin[0] == 1){ // se entrar nesta condicional, sera desfeito o complemento de dois.
        for(int i = bin.size()-1;i >= 0;i--){
            if(baux == true)
                bin[i] = ((bin[i] == '0') ? '1' : '0');
            else if(bin[i] == '1') // percorre a string da direita pra esquerda e
                baux = true;       // quando encontrar o primeiro 1, repete ele e inverte o restante.
        }
    }
    for (int i = 0; i < bin.size(); i++) {
        if (bin[i] == 0x31)
            result += pow(2, bin.size() - i - 1);
    }
    return (baux) ? result*-1 : result;
}

/*
 * Este metodo converte um numero decimal para um numero binario.
 */
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
    if(dec < 0){ // se o numero for negativo sera realizado o complemento de dois.
        for(int i = 0;i < aux.size();i++){
            if(baux == true)
                aux[i] = ((aux[i] == '0') ? '1' : '0');
            else if(aux[i] == '1')
                baux = true;
        }
        res = extend(string(aux.rbegin(), aux.rend()), '1',ext); // preenche com 1 se for negativo.
    }else{
        res = extend(string(aux.rbegin(), aux.rend()), '0',ext); // preenche com 0 se for positivo.
    }
    return res;
}

/*
 * Este metodo converte um numero binario para um numero hexadecimal.
 */
string Conversion::binToHex(string bin){
    string resp;
    for(int i = 0;i <= bin.length()-4;i+=4){
        string aux(bin,i,4);
        int sullivan = binToDec(aux);
        if(sullivan > 9){
            sullivan += 0x37;
        }else{
            sullivan += 0x30;
        }
        resp += sullivan;
    }
    return resp;
}

/*
 * Este metodo converte um numero hexadecimal para um numero binario.
 */
string Conversion::hexToBin(string hex){
    string resp;
    for(int i = 0; i < hex.length(); i++){
        if(!isalpha(hex[i])){
            resp += decToBin(hex[i] - 0x30,4);
        }else{
            resp += decToBin(hex[i] - 0x37,4);
        }
    }
    return resp;
}