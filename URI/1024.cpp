#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <iostream>
using namespace std;
int main(){
    int N;
    scanf("%d ", &N);
    string code;
    while(N-->0){
        char aux;
        getline(cin, code);
        for (int i=0; i<code.size(); i++){
            if ((code[i]>='a' && code[i]<='z') || (code[i]>='A' && code[i]<='Z'))
                code[i]+=3;
        }
        for (int i=0; i<code.size()/2; i++){
            aux=code[i];
            code[i]=code[code.size()-1-i];
            code[code.size()-1-i]=aux;
        }
        for (int i=code.size()/2; i<code.size(); i++){
            code[i]--;
        }
        printf ("%s\n", code.c_str());
    }
    return 0;
}
