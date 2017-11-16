#include <bits/stdc++.h>
using namespace std;
#define MAXN 109
#define state dp[k][s][r][m]

typedef long long ll;
//dp[k][s][r][m] = menor que 10^k, soma dos digitos s, resto r na divisao por m,
int vet[20];
ll dp[13][MAXN][MAXN][MAXN];
ll pten[20];

void init(){
    for(int k=0; k<13; k++){
        for(int s=0; s<MAXN; s++){
            for(int r=0; r<MAXN; r++){
                for(int m=0; m<MAXN; m++){
                    state = -1;
                }
            }
        }
    }
    pten[0] = 1;
    for(int k=1; k<20; k++) pten[k] = 10*pten[k-1];
}

ll DP(const int k, const int s, const int r, const int m){
    if (state >= 0) return state;
    if (k == 0) return state = ((r == 0) && (s == 0));
    int mod;
    state = 0;
    for(int i=0; i<=9 && i<=s; i++){
        mod = (r - ((i*pten[k-1])%m) + m)%m;
        state += DP(k-1, s-i, mod, m);
    }
    return state;
}

int main(){
    freopen("just.in", "r", stdin);
    freopen("just.out", "w", stdout);

    init();
    ll n;
    int K = 0, MAXS = 0;
    scanf("%I64d", &n);
    for(int i=0; i<20; i++){
        vet[i] = n%10;
        MAXS += vet[i];
        if (vet[i] > 0) K = i;
        n /= 10;
    }
    ll ans = 0;
    for(int S=1; S<MAXN; S++){
        int s = S;
        int mod = 0;
        for(int k=K; k>=0; k--){
            for(int i=0; i<vet[k] && i<=s; i++){
                ans += DP(k, s-i, (mod - ((i*pten[k])%S) + S)%S, S);
            }
            s -= vet[k];
            mod = (mod - ((vet[k]*pten[k])%S) + S)%S;
        }
        if (s == 0 && mod == 0) ans++;
    }
    printf("%I64d\n", ans);

    fclose(stdin);
    fclose(stdout);
    return 0;
}