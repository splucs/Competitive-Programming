#include <bits/stdc++.h>
using namespace std;
#define MAXN 509
#define MOD 1000000009
#define state dp[i][v][d]

typedef long long ll;
int K, N, win[MAXN];
ll dp[MAXN][MAXN][MAXN], pascal[MAXN][MAXN];
int a[MAXN], b[MAXN];

ll Pascal(const int n, const int k) {
	if (pascal[n][k] >= 0) return pascal[n][k];
	if (k == 0 || n == k) return pascal[n][k] = 1;
	if (k > n) return pascal[n][k] = 0;
	return pascal[n][k] = (Pascal(n-1, k-1) + Pascal(n-1, k))%MOD;
}

ll DP(const int i, const int v, const int d) {
	if (state >= 0) return state;
	if (v > K) return state = 0;
	if (i == 0) return state = (v == K);
	int td = N-i-v-d;
	state = 0;
	for(int j=0; j<=td; j++) {
		state = (state + (((win[i]-v-d-j)*Pascal(win[i]-win[i+1], j))%MOD)*DP(i-1, v+1, d+j))%MOD;
		state = (state + (((N-win[i]-td+j)*Pascal(win[i]-win[i+1], j))%MOD)*DP(i-1, v, d+j))%MOD;
	}
	printf("dp[%d][%d][%d] = %I64d\n", i, v, d, state);
	return state;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	scanf("%d %d", &N, &K);
	for(int i=1; i<=N; i++) {
		scanf("%d", &a[i]);
	}
	sort(a+1, a+1+N);
	for(int i=1; i<=N; i++) {
		scanf("%d", &b[i]);
	}
	sort(b+1, b+1+N);
	for(int i=N, j=0; i>0; i--) {
		while(b[i] < a[N-j]) j++;
		win[i] = j;
		printf("win[%d]= %d\n", i, win[i]);
	}
	win[N+1] = 0;
	for(int i=0; i<MAXN; i++) {
		for(int j=0; j<MAXN; j++) {
			pascal[i][j] = -1;
			for(int k=0; k<MAXN; k++) {
				dp[i][j][k]=-1;
			}
		}
	}
	printf("%I64d\n", DP(N, 0, 0));
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}