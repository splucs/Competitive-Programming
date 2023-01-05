#include <cstdio>
#include <cstring>
#define MAXN 209
#define INF (1<<29)
#define max(a,b) (a>b?a:b)
#define INTLIMIT 2147483647

typedef long long ll;
ll dp[MAXN], s2i[MAXN][MAXN];
char str[MAXN];

ll str2int(int a, int b){
    ll res=0, p=1;
    for(int i=b; i>=a; i--, p*=10){
        res += ((ll)(str[i]-'0'))*p;
        if (res>INTLIMIT) return 0;
    }
    return res;
}

ll DP(int n){
    if (n<0) return 0;
    if (dp[n]>=0) return dp[n];
    dp[n] = 0;
    for(int i=n-1; i>=-1; i--){
        dp[n] = max(dp[n], DP(i) + s2i[i+1][n]);
    }
    return dp[n];
}

int main(){
    int N, n;
    scanf("%d", &N);
    while(N-->0){
        scanf(" %s", str);
        n = strlen(str);
        for(int i=0; i<n; i++){
            dp[i]=-1;
            for(int j=i; j<n; j++){
                s2i[i][j] = str2int(i, j);
            }
        }
        printf("%lld\n", DP(n-1));
    }
    return 0;
}
