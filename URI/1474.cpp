#include <stdio.h>
typedef long long lint;
#define mod 10000000
lint N, K, L;

struct mat
    {int a, b, c, d};

mat expo (lint expoente){
    if (expoente==1)
        return pot1;
    mat potmetade=expo(expoente/2);
    mat resp=multiplica(potmetade, potmetade;
}

lint f(lint n){
    if (n==1)
        return 1;
    else if (n==2)
        return (L*L+K)%mod;
    mat resposta = expo(pot1, n-1);
    return (resposta.a*f(1)+resposta.b*f(2))%mod;
}
int main(){
    while (scanf(" %lld %lld %lld", &N, &K, &L)!=EOF){
        K%=mod;
        L%=mod;
        pot1.a=0;
        pot1.b=1;
        pot1.c=L;
        pot1.d=K;

    }
}
