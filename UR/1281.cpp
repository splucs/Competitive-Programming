#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <map>
#include <algorithm>
#include <iostream>

using namespace std;

int main(){
    int N;
    cin >> N;
    while (N>0){
        int M, P;
        float quantia=0;
        cin >> M;
        map<string, float>precos;
        while (M>0){
            string fruta;
            float preco;
            cin >> fruta;
            cin >> preco;
            precos[fruta]=preco;
            M--;
        }
        cin >> P;
        while (P>0){
            string fruta;
            float quant;
            cin >> fruta;
            cin >> quant;
            quantia+=quant*precos[fruta];
            P--;
        }
        printf ("R$ %.2lf\n", quantia);
        N--;
    }
    return 0;
}
