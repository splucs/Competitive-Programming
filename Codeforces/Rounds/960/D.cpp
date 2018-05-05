#include <bits/stdc++.h>
using namespace std;
#define MAXN 63
#define MAXM ((1e+18) + 100)
#define MOD 1000000007
#define INF 1000000009
#define EPS 1e-9
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define pb push_back
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;
#define EPS 1e-9

ll sz[MAXN], en[MAXN], shift[MAXN];

int getlevel(ll X) {
	int ans = 0;
	while(X != 1) {
		ans++;
		X >>= 1;
	}
	return ans;
}

ll getpos(ll X) {
	int i = getlevel(X);
	ll num = X - en[i];
	num += shift[i];
	num %= sz[i];
	num += en[i];
	return num;
}

ll getnum(ll pos) {
	int i = getlevel(pos);
	ll num = pos - en[i];
	num = (num - shift[i] + sz[i]) % sz[i];
	return num + en[i];
}

int main() {
	FOR(i, MAXN) {
		sz[i] = en[i] = (1LL<<i);
		shift[i] = 0;
	}
	int Q;
	scanf("%d", &Q);
	while(Q --> 0) {
		int op;
		ll X, K;
		scanf("%d", &op);
		if (op == 1) {
			scanf("%I64d %I64d", &X, &K);
			int i = getlevel(X);
			K = (K % sz[i] + sz[i]) % sz[i];
			shift[i] += K;
			shift[i] %= sz[i];
		}
		if (op == 2) {
			scanf("%I64d %I64d", &X, &K);
			int i = getlevel(X);
			K = (K % sz[i] + sz[i]) % sz[i];
			for(; i < MAXN; i++) {
				shift[i] += K;
				shift[i] %= sz[i];
				K <<= 1;
			}
		}
		if (op == 3) {
			scanf("%I64d", &X);
			ll pos = getpos(X);
			while (pos > 0) {
				printf("%I64d ", getnum(pos));
				pos >>= 1;
			}
			printf("\n");
		}
	}
	return 0;
}
