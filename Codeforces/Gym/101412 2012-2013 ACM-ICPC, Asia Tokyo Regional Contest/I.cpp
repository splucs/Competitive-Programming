#include <bits/stdc++.h>
using namespace std;
#define MAXN 50009
#define INF (1<<30)

int dp[MAXN], dpsum[MAXN], x[MAXN], px[MAXN], l[MAXN], r[MAXN], W, N;

int check(int limit) {
	dp[N+1] = dp[N+2] = dp[N] = dp[N-1] = 1;
	l[N-1] = r[N-1] = N;
	
	dpsum[N+2] = 0;
	dpsum[N+1] = 1;
	dpsum[N] = 2;
	dpsum[N-1] = 3;
	
	//printf("limit = %d\n", limit);
	
	for(int i=N-2; i>0; i--) {
		
		l[i] = l[i+1];
		while(l[i]-1 > i) {
			int j = l[i] - 1;
			int left = W - (px[j] - px[i-1]), space;
			if (j == N) space = 1;
			else if (left%(j-i) == 0) space = left/(j-i);
			else space = left/(j-i) + 1;
			if (space <= limit) l[i]--;
			else break;
		}
		//printf("%d to %d: %d spaces\n", i, j, space);
		
		r[i] = r[i+1];
		while(true) {
			int j = r[i];
			int used = px[j] - px[i-1] + j-i;
			if (used <= W) break;
			else r[i]--;
		}
		
		dp[i] = dpsum[l[i]+1] - dpsum[r[i]+2] > 0 ? 1 : 0;
		dpsum[i] = dp[i] + dpsum[i+1];
		
		//printf("%d: %d to %d -> %d\n", i, l, r, dp[i]);
	}
	
	return dp[1];
}

int main() {
	while(scanf("%d %d", &W, &N), W || N) {
		px[0] = 0;
		for(int i=1; i<=N; i++) {
			scanf("%d", &x[i]);
			px[i] = x[i] + px[i-1];
		}
		
		int lo = 0;
		int hi = W;
		while(hi > lo + 1) {
			int mid = (hi + lo) / 2;
			if (check(mid)) hi = mid;
			else lo = mid;
		}
		
		printf("%d\n", hi);
	}
	return 0;
}