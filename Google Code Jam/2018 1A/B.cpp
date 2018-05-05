#include <bits/stdc++.h>
using namespace std;
#define MAXN 10009
#define MOD 1000000007
#define INF (1LL<<60)
#define EPS 1e-7
#define FOR(x,n) for(int x=0; x<n; x++)
#define FOR1(x,n) for(int x=1; x<=n; x++)
#define pb push_back
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;

ll M[MAXN], S[MAXN], P[MAXN];
int R, B, C;

ll t;
ll howmuch(int i) {
	return min(M[i], max(t - P[i], 0LL) / S[i]);
}

bool comp(int i, int j) {
	return howmuch(i) > howmuch(j);
}
int id[MAXN];

bool check(ll _t) {
	t = _t;
	sort(id, id+C, comp);
	ll left = B;
	FOR(i, R) {
		ll cur = howmuch(id[i]);
		left -= cur;
	}
	return left <= 0;
}

int main() {
	int T;
	scanf("%d", &T);
	FOR1(caseNo, T) {
		scanf("%d %d %d", &R, &B, &C);
		FOR(i, C) {
			id[i] = i;
			scanf("%lld %lld %lld", &M[i], &S[i], &P[i]);
		}
		ll lo = 0;
		ll hi = INF;
		while(hi > lo + 1) {
			ll mid = (hi + lo) / 2;
			if (check(mid)) hi = mid;
			else lo = mid;
		}
		printf("Case #%d: %lld\n", caseNo, hi);
	}
	return 0;
}