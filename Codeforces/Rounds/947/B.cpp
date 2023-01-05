#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
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

ll rsq(ll bit[], int i) {
	ll ans = 0;
	while(i > 0) {
		ans += bit[i];
		i -= (i&-i);
	}
	return ans;
}

ll rsq(ll bit[], int i, int j) {
	return rsq(bit, j) - rsq(bit, i-1);
}

void update(ll bit[], int i, ll v) {
	while(i < MAXN) {
		bit[i] += v;
		i += (i&-i);
	}
}

int N;
ll V[MAXN], T[MAXN];
ll sumbit[MAXN], cntbit[MAXN];

int main() {
	scanf("%d", &N);
	FOR1(i, N) scanf("%I64d", &V[i]);
	FOR1(i, N) scanf("%I64d", &T[i]);
	map<ll, int> reduce;
	ll tot = 0;
	reduce[tot+1] = 0;
	FOR1(i, N) {
		V[i] += tot;
		tot += T[i];
		reduce[tot+1] = 0;
	}
	FOR1(i, N) reduce[V[i]] = 0;
	int cnt = 0;
	for(auto & pp : reduce) {
		pp.second = ++cnt;
	}
	tot = 0;
	FOR1(i, N) {
		update(sumbit, reduce[V[i]], V[i]);
		update(cntbit, reduce[V[i]], 1);
		ll prv = rsq(sumbit, reduce[tot+1], MAXN-1);
		prv -= rsq(cntbit, reduce[tot+1], MAXN-1)*tot;
		tot += T[i];
		ll nxt = rsq(sumbit, reduce[tot+1], MAXN-1);
		nxt -= rsq(cntbit, reduce[tot+1], MAXN-1)*tot;
		printf("%I64d ", prv - nxt);
	}
	printf("\n");
	return 0;
}