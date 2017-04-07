#include <cstdio>
#include <map>
using namespace std;

typedef struct formigueiro{
    int num;
    int pai;
    long long int distPai;
    int profundidade;
    map<int, long long int> filhos;
}formigueiro;

formigueiro form[100000];

void definirProf(int node, int h){
    form[node].profundidade=h;
    map<int, long long int>::iterator it;
    for (it=form[node].filhos.begin(); it!= form[node].filhos.end(); it++){
        definirProf(it->first, h+1);
    }
}

int main()
{
    int N, A, Q, x, y;
    long long int dist, L;
    for (int i=0; i<100000; i++) form[i].num=i;
    while(true){
        scanf("%d", &N);
        if (N==0) break;
        for (int i=0; i<N; i++) form[i].filhos.clear();
        for (int i=1; i<N; i++){
            scanf("%d %lld", &A, &L);
            form[A].filhos[i]=L;
            form[i].pai=A;
            form[i].distPai=L;
        }
        definirProf(0, 0);
        scanf("%d", &Q);
        for (int q=0; q<Q; q++){
            dist=0;
            scanf("%d %d", &x, &y);
            while (form[x].profundidade>form[y].profundidade){
                dist+=form[x].distPai;
                x=form[x].pai;
            }
            while (form[x].profundidade<form[y].profundidade){
                dist+=form[y].distPai;
                y=form[y].pai;
            }
            while (x!=y){
                dist+=form[y].distPai;
                y=form[y].pai;
                dist+=form[x].distPai;
                x=form[x].pai;
            }
            printf("%lld", dist);
            if (q<Q-1) printf(" ");
        }
        printf("\n");
    }
    return 0;
}
