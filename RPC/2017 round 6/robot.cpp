#include <bits/stdc++.h>
using namespace std;
#define state dp[r][c]

typedef long long ll;
ll dp[30][30];

ll DP(int r, int c){
    if (state >= 0) return state;
    if (c == 1) return state = 1;
    state = 0;
    for(int k=1; k<=r; k++)
        state += DP(c-1, k);
    return state;
}

int main() {
    int T, r, c;
    scanf("%d", &T);
    for(r=0; r<30; r++) for(c=0; c<30; c++) state = -1;
    while(T-->0){
        scanf("%d %d", &r, &c);
        printf("%lld\n", DP(r, c));
    }
    return 0;
}
