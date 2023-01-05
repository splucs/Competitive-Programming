#include <bits/stdc++.h>
using namespace std;
#define MAXN 60009
#define state dp[mask][k][b][z]

typedef long long ll;

ll dp[MAXN][20][2][2];
int v[20];

void mask2arr(int mask, int* arr) {
	int i=0;
	for(int i=0; i<10; i++) {
		arr[i] = mask%3;
		mask /= 3;
	}
}

int arr2mask(int * arr) {
	int mask = 0;
	for(int i=9; i>=0; i--) {
		mask *= 3;
		mask += arr[i];
	}
	return mask;
}

ll DP(const int mask, const int k, const int b, const int z) {
	if (k < 0) return 1;
	if (state >= 0) return state;
	int arr[10], nmask;
	mask2arr(mask, arr);
	state = 0;
	for(int i=0; i<=(b ? v[k] : 9); i++) {
		if (arr[i] == 2) continue;
		if (!z || i>0) arr[i]++;
		nmask = arr2mask(arr);
		if (!z || i>0) arr[i]--;
		state += DP(nmask, k-1, b && i==v[k] ? 1:0, z && i==0 ? 1:0);
	}
	return state;
}

ll solve(ll x) {
	memset(&v, 0, sizeof v);
	int N = 0;
	while(x > 0) {
		v[N++] = x%10;
		x /= 10;
	}
	for(int mask=0; mask < MAXN; mask++) {
		for(int k=0; k<N; k++) {
			dp[mask][k][0][0] = dp[mask][k][1][0] = -1;
			dp[mask][k][0][1] = dp[mask][k][1][1] = -1;
		}
	}
	ll ans = 0;
	return DP(0, N-1, 1, 1);
}

int main() {
	freopen("exchange.in", "r", stdin);
	freopen("exchange.out", "w", stdout);
	
	ll l, r;
	while(!feof(stdin)) {
		scanf(" %I64d %I64d ", &l, &r);
		printf("%I64d\n", solve(r) - solve(l-1));
	}
		
	fclose(stdin);
	fclose(stdout);
	return 0;
}