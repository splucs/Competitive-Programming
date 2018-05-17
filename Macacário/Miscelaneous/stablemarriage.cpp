#include <cstdio>
#include <cstring>
#define MAXN 1009

int m, n;     //número de homens e de mulheres
int p[MAXN];
int L[MAXN][MAXN];    //L[i]: preferências do homem i (melhor primeiro)
int R[MAXN][MAXN];    //R[j][i]: nota dada pela mulher j ao homem i
int R2L[MAXN];  //R2L[i]==j: mulher i casada com homem j 
int L2R[MAXN];  //L2R[i]==j: homem i casado com mulher j 

void stableMarriage() {
    memset(R2L, -1, sizeof(R2L));
    memset(p, 0, sizeof(p));
    for(int i = 0, wom, hubby; i < m; i++) {
        for (int man = i; man >= 0;) {
            while(true) {
                wom = L[man][p[man]++];
                if( R2L[wom] < 0 || R[wom][man] > R[wom][R2L[wom]] ) break;
            }
            hubby = R2L[wom];
            R2L[L2R[man] = wom] = man;
            man = hubby;
        }
    }
}

int main() {
    int t, ma, wo, rank;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        m = n;
        for(int i=0; i<n; i++) {
            scanf("%d", &wo);
            rank = n;
            for(int j=0; j<n; j++, rank--) {
                scanf("%d", &ma);
                R[wo-1][ma-1] = rank;
            }
        }
        for(int i=0; i<n; i++) {
            scanf("%d", &ma);
            for(int j=0; j<n; j++) {
                scanf("%d", &L[ma-1][j]);
                L[ma-1][j]--;
            }
        }
        stableMarriage();
        for(int i=0; i<n; i++) {
            printf("%d %d\n", i+1, L2R[i]+1);
        }
    }
    return 0;
}
