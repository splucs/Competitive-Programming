#include <bits/stdc++.h>

using namespace std;

typedef pair<double, int> ii;

int sign(int x){
    if(x>0) return 1;
    return -1;
}

int main(){
    ii vet[100100];
    int a, b;
    int x, y;
    int n;
    int zero = 0;
    int maior = 0;
    int infinito = 0;
    int menor = 0;
    int tam = 0;
    cin>>n;
    cin>>a>>b;
    n--;
    for(int i = 0; i<n; i++){
        cin>>x>>y;
        if(b!=y){
            vet[tam++] = ii(1.0*(x-a)/(b-y), sign(b-y));
        }

        if(a<x || (a==x && y<=b)) zero++;
        if(y<b || (y==b && x<=a)) infinito++;
        if(y<=b) menor++;
        if(y>=b) maior++;

        // cout<<"y = "<<y<<"\tb = "<<b<<endl;
    }
    // cout<<"tam = "<<tam<<endl;
    // cout<<"zero = "<<zero<<" inf = "<<infinito<<" maior = "<<maior<<" menor = "<<menor<<endl;


    sort(vet, vet+tam);


    int atual = zero;
   
    maior = max(maior, zero);
    for(int i = 0; i<tam; i++){
        // cout<<"i = "<<i<<endl;
        if(vet[i].first>-0.000001){
            atual-=vet[i].second;
            // cout<<vet[i].first<<" "<<vet[i].second<<" atual = "<<atual<<endl;
            maior = max(maior, atual);
        }
        vet[i].second *=-1;
    }
    atual = infinito;
    sort(vet, vet+tam);
    for(int i = tam-1; i>=0; i--){
        if(vet[i].first>-0.000001){
            atual+=vet[i].second;
            menor = max(menor, atual);
        }
    }

    // cout<<maior<<" "<<menor<<endl;
    cout<<n-menor+1<<" "<<maior+1<<endl;
}