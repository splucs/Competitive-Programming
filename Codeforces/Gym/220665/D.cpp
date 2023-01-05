#include <bits/stdc++.h>
using namespace std;
#define MAXN 59

typedef long long ll;
ll sz[MAXN];

int solve(int n, ll k) {
	if (k == sz[n] + 1) return n + 1;
	else if (k < sz[n] + 1) return solve(n - 1, k);
	else return solve(n, k - sz[n] - 1);
}

int main() {
	sz[1] = 1;
	for(int i = 2; i < MAXN; i++) sz[i] = 2*sz[i-1] + 1;
	int N;
	ll K;
	scanf("%d %I64d", &N, &K);
	printf("%d\n", solve(N, K));
	return 0;
}