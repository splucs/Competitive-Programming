#include <bits/stdc++.h>
using namespace std;
#define MAXN 409
#define INF (1<<30)
#define state dp[i][si][vi]

int dp[409][1509][59];

int v[MAXN], s[MAXN], N, S, maxv, minv;

int DP(const int i, const int si, const int vi) {
	if (vi < minv || vi > maxv || si < 0) return INF;
	if (state >= 0) return state;
	if (i == 0){
		if (si != 0) return state = INF;
		else return state = 0;
	}
	state = INF;
	for(int vj = vi-1; vj <= vi+1; vj++) {
		state = min(state, DP(i-1, si-vj, vj));
	}
	state += abs(s[i] - si);
	return state;
}

int main() {
	scanf("%d", &N);
	S = 0;
	for(int i=1; i<=N; i++) {
		scanf("%d", &v[i]);
		S += v[i];
	}
	minv = 0;
	maxv = 0;
	int d = 1, cs=0;
	while(cs + d <= S){
		cs += d;
		maxv++;
		if (d < N) d++;
		else minv++;
	}
	maxv++;
	if (minv > 0) minv--;
	s[0] = 0;
	for(int i=1; i<=N; i++) {
		v[i] -= minv;
		s[i] = v[i] + s[i-1];
	}
	maxv -= minv;
	minv -= minv;
	int ans = INF;
	for(int i=0; i<=N; i++) {
		for(int si=0; si<=S; si++){
			for(int vi=minv; vi<=maxv; vi++) state = -1;
		}
	}
	for(int i=minv; i<=maxv; i++) {
		ans = min(ans, DP(N, s[N], i));
	}
	printf("%d\n", ans);
	return 0;
}