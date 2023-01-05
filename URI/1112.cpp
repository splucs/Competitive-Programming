#include <map>
#include <cstdio>
using namespace std;

int main(){
    int X, Y, P, Q, x1, x2, y1, y2, n;
    char order;
    map<int, map<int, int> > ::iterator it1;
    map<int, int>::iterator it2;
    while (true){
        scanf("%d %d %d", &X, &Y, &P);
        if (X==0 && Y==0 && P==0) break;
        scanf("%d", &Q);
        map<int, map<int, int> > mapa;
        for (int q=0; q<Q; q++){
            scanf(" %c", &order);
            if (order=='A'){
                scanf("%d %d %d", &n, &x1, &y1);
                if(mapa.find(x1)!=mapa.end() && mapa[x1].find(y1)!=mapa[x1].end())
                    mapa[x1][y1]+=n;
                else mapa[x1][y1]=n;
            }
            else if (order=='P'){
                scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
                if (x2<x1){
                    n=x1;
                    x1=x2;
                    x2=n;
                }
                if (y2<y1){
                    n=y1;
                    y1=y2;
                    y2=n;
                }
                n=0;
                for (it1=mapa.begin(); it1!=mapa.end() && it1->first<x1; it1++);
                for (; it1!=mapa.end() && it1->first<=x2; it1++){
                    for(it2 = it1->second.begin(); it2!=it1->second.end() && it2->first<y1; it2++);
                    for(; it2!=it1->second.end() && it2->first<=y2; it2++){
                        n+=it2->second;
                    }
                }
                printf("%d\n", n*P);
            }
        }
        printf("\n");
    }
    return 0;

}

