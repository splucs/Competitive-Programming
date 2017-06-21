#include <bits/stdc++.h>
using namespace std;
#define MAXN 50009
#define state dp[i][s][k]

typedef long long ll;
ll dp[51][MAXN][11];
int v[51];

ll DP(const int i, const int s, const int k) {
	if (state >= 0) return state;
	if (i == 0 || k==0){
		return state = (s==0 && k==0);
	}
	return state = DP(i-1, s, k) + DP(i-1, max(0, s-v[i]), k-1);
}

int main() {
	int N, K;
	scanf("%d", &N);
	for(int i=1; i<=N; i++){
		scanf("%d", &v[i]);
	}
	scanf("%d", &K);
	sort(v+1, v+N+1);
	for(int i=0; i<=N; i++){
		for(int s=0; s<MAXN; s++) {
			for(int k=0; k<K; k++) state = -1;
		}
	}
	ll ans = 0;
	for(int i=1; i<=N; i++){
		ans += DP(i-1, v[i]+1, K-1);
	}
	printf("%I64d\n", ans);
	return 0;
}