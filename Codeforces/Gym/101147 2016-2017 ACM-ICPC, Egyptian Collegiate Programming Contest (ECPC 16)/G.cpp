#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009
#define MOD 1000000007LL

typedef long long ll;
ll pascal[MAXN][MAXN];

ll modExp(ll a, ll b) {
	if (b == 0) return 1;
	ll c = modExp(a, b/2);
	c = (c*c)%MOD;
	if (b%2 != 0) c = (c*a)%MOD;
	return c;
}

int main() {
	freopen("galactic.in", "r", stdin);
	
	for(int i=0; i<MAXN; i++) {
		for(int j=0; j<MAXN; j++) {
			if (j > i) pascal[i][j] = 0;
			else if (j == 0 || i == j) pascal[i][j] = 1;
			else pascal[i][j] = (pascal[i-1][j]+pascal[i-1][j-1]) % MOD;
		}
	}
	
	int T;
	ll N, K, ans;
	scanf(" %d ", &T);
	while(T-->0) {
		scanf(" %I64d %I64d ", &N, &K);
		if (K > N) {
			printf("0\n");
			continue;
		}
		ans = 0;
		for(ll i=0; i<K; i++) {
			if (i % 2 == 0) ans = (ans + (pascal[K][i]*modExp(K-i, N))%MOD) % MOD;
			else ans = (ans - (pascal[K][i]*modExp(K-i, N))%MOD + MOD) % MOD;
		}
		printf("%I64d\n", ans);
	}
	
	fclose(stdin); 
	return 0;
}