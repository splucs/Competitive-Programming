#include <bits/stdc++.h>
using namespace std;
#define MAXN 1509
#define INF (1<<30)
#define state dp[i][sp][in]

int dp[409][409][MAXN];

int vet[MAXN], N, S, maxv;

int DP(const int i, const int sp, const int in) {
	const int rin = in-S;
	if (rin < 0 || rin > 2*S) return INF;
	if (state >= 0) return state;
	if (i == N) {
		return state = (in == 0 ? 0 : INF);
	}
	if (abs(in) >= maxv) return state = INF;
	int ans = INF;
	for(int sc = max(0, sp-1); sc <= min(sp+1, maxv); sc++) {
		//if (i == 0) sc = sp;
		int nin = rin+vet[i]-sc;
		ans = min(ans, abs(nin) + DP(i+1, sc, S+nin));
		//if (i == 0) break;
	}
	return state = ans;
}

bool canmaxv() {
	int ans = 0;
	for(int i=0; i<N; i++){
		ans += maxv-i;
	}
	return ans <= S;
}

int main() {
	scanf("%d", &N);
	S = 0;
	for(int i=0; i<N; i++) {
		scanf("%d", &vet[i]);
		S += vet[i];
	}
	//maxv = 1;
	//while(canmaxv()) maxv++;
	//maxv--;
	maxv = MAXN-1;
	//printf("maxv = %d\n", maxv);
	int ans = INF;
	memset(&dp, -1, sizeof dp);
	for(int i=0; i<=maxv; i++) {
		ans = min(ans, DP(0, i, S));
	}
	printf("%d\n", ans);
	return 0;
}