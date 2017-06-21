#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <stack>
#include <iostream>

using namespace std;

int main(){
    int N;
    string linha;
    stack <char> pilha;
    scanf ("%d", &N);
    int contador[N], n, pilha_size;
    n=N;
    for (int m=0; m<N; m++)
        contador[m]=0;
    while (N>0){
        cin >> linha;
        for (int m=0; m<linha.size(); m++){
            if (linha[m]!='.'){
                if (pilha.empty() && linha[m]=='<'){
                    pilha.push(linha[m]);
                }
                else if (!pilha.empty() && pilha.top()=='<' && linha[m]=='<'){
                    pilha.push(linha[m]);
                }
                else if (!pilha.empty() && pilha.top()=='<' && linha[m]=='>'){
                    pilha.pop();
                    contador[N-1]++;
                }
            }
        }
        pilha_size=pilha.size();
        for (int m=0; m<pilha_size; m++)
            pilha.pop();
        N--;
    }
    for (int m=0; m<n; m++)
        printf ("%d\n", contador[n-1-m]);
    return 0;
}
