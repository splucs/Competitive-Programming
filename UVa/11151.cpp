#include <cstdio>
#include <cstring>
#define MAXN 1009
#define max(a,b) (a<b?b:a)

int dp[MAXN][MAXN];
char str[MAXN];

int DP(int a, int b){
    if (a>b) return 0;
    if (dp[a][b]>=0) return dp[a][b];
    dp[a][b] = max(DP(a+1, b), DP(a, b-1));
    if (str[a]==str[b]) dp[a][b] = max(dp[a][b], (a==b?1:2)+DP(a+1, b-1));
    return dp[a][b];
}

int main(){
    int T, n;
    scanf("%d", &T);
    getc(stdin);
    while(T-->0){
        gets(str);
        n = strlen(str);
        for(int i=0; i<n; i++) for(int j=0; j<n; j++) dp[i][j]=-1;
        printf("%d\n", DP(0, n-1));
    }
    return 0;
}
