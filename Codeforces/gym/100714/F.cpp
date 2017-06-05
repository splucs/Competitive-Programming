#include <bits/stdc++.h>

using namespace std;

struct node{
    int inicio, peso, cap;
    node(){
        inicio = peso = cap = 0;
    }
    node(int i, int p, int c){
        inicio = i;
        peso = p;
        cap = c;
    }
    void print(bool b){
        for(int i = 0; i<peso; i++){
            if(b) b = false;
            else printf(" ");
            printf("%d", inicio+i);
        }
    }
};

struct conjunto{
    node elem[4];
    conjunto(node f = node(), node s = node(), node t = node(), node o = node()){
        elem[0] = f;
        elem[1] = s;
        elem[2] = t;
        elem[3] = o;
    }
    void print(){
        for(int i = 0; i<4; i++)
            elem[i].print(i==0);
        cout<<endl;
    }
};

int main(){
    conjunto vet[20];
    vet[0] = conjunto(node(1, 4, 0));
    vet[1] = conjunto(node(1, 3, 0), node(5, 1, 3));
    vet[2] = conjunto(node(1, 2, 0), node(4, 2, 2));
    vet[3] = conjunto(node(1, 1, 0), node(3, 3, 1));
    vet[4] = conjunto(node(1, 2, 0), node(4, 1, 2), node(6, 1, 3));
    vet[5] = conjunto(node(1, 1, 0), node(3, 2, 1), node(6, 1, 3));
    vet[6] = conjunto(node(1, 1, 0), node(3, 1, 1), node(5, 2, 2));
    vet[7] = conjunto(node(1, 1, 0), node(3, 1, 1), node(5, 1, 2), node(7, 1, 3));
    
    int idMelhor = 0;
    int valMelhor = -1;
    int atual;
    int info[5];
    for(int i = 0; i<4; i++){
        cin>>info[i];
    }
    for(int i = 0; i<8; i++){
        atual = 0;
        for(int k = 0; k<4; k++){            
            for(int j = 0; j<4; j++){
                if(info[j]>=vet[i].elem[k].inicio) atual+=vet[i].elem[k].peso;
            }
            atual+=vet[i].elem[k].cap*vet[i].elem[k].peso;
        }
        // cout<<atual<<": ";
        // vet[i].print();
        if(atual>valMelhor){
            valMelhor = atual;
            idMelhor = i;
        }
    }
    vet[idMelhor].print();

}