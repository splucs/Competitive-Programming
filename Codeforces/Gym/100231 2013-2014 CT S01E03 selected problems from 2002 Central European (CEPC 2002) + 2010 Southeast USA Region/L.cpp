#include <bits/stdc++.h>
using namespace std;
#define MAXN 70

typedef long long ll;

ll pascal[MAXN][MAXN];
int steps[MAXN];

int countBits(ll n) {
	int ans = 0;
	while(n > 0) {
		ans++;
		n -= (n & -n);
	}
	return ans;
}

ll query(ll n, int X) {
	int cb = countBits(n) - 1;
	ll ans = 0;
	while(n > 0) {
		ll lb = (n & -n);
		int k = 0;
		while((1LL<<k) < lb) k++;
		for(int nb = 0; nb <= k; nb++) {
			if (steps[cb + nb] + 1 == X)
				ans += pascal[k][nb];
		}
		n -= lb;
		cb--;
	}
	return ans;
}

int main() {
	for(int n=0; n<MAXN; n++) {
		for(int k=0; k<MAXN; k++) {
			if (k > n) pascal[n][k] = 0;
			else if (k == 0 || n == k) pascal[n][k] = 1;
			else pascal[n][k] = pascal[n-1][k] + pascal[n-1][k-1];
		}
	}
	
	steps[1] = 0;
	for(int i=2; i<MAXN; i++) {
		steps[i] = 1 + steps[countBits(i)];
		//printf("steps[%d] = %d\n", i, steps[i]);
	}
	
	ll l, r;
	int X;
	while(scanf("%I64d %I64d %d", &l, &r, &X), l || r || X) {
		if (X==0){
			if (l<=1&&r>=1)cout<<1<<endl;
			else cout<<0<<endl;
			continue;
		}
		if (l==1)l++;
		printf("%I64d\n", query(r+1, X) - query(l, X));
	}
	
	return 0;
}