#include <cstdio>
#include <algorithm>

bool f(int a, int b){
    return a>b;
}

int main()
{
    int T, D, P[1005], paradas, x, mini;
    scanf("%d", &T);
    for (int caso=1; caso<=T; caso++){
        scanf("%d", &D);
        for (int i=0; i<D; i++){
            scanf("%d", P+i);
        }
        std::sort(P, P+D, f);
        mini=P[0];
        for (int altura=1; altura<P[0]; altura++){
            paradas=0;
            for (int i=0; i<D; i++){
                if (P[i]<=altura || paradas+altura>mini) break;
                if ((P[i]-altura)%altura!=0) paradas++;
                paradas+=(P[i]-altura)/altura;
            }
            mini=(mini<altura+paradas?mini:altura+paradas);
        }
        printf("Case #%d: %d", caso, mini);
        if (caso<T) printf("\n");
    }
    return 0;
}
