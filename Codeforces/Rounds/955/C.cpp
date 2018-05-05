#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000009
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

map<ll, int> numb;
bitset<MAXN> ispow2;

void preprocess() {
	ispow2.reset();
	for(ll i = 1; i*i < MAXN; i++) {
		ispow2[i*i] = 1;
	}
	for(ll a = 2; a < MAXN; a++) {
		if (ispow2[a] || numb.count(a*a*a)) continue;
		ll pa = a;
		int ex = 1;
		while(MAXM/a + 1 >= pa) {
			pa *= a;
			ex++;
			if (ex % 2 != 0) numb[pa] = 0;
		}
	}
	numb[MAXM] = 0;
	int cnt = 0;
	for(auto & pp : numb) {
		pp.second = ++cnt;
	}
}

ll between(ll L, ll R) {
	return numb.upper_bound(R)->second - numb.lower_bound(L)->second;
}

ll query(ll L, ll R) {

	ll s1 = sqrt(L);
	if (s1*s1 < L) s1++;
	ll s2 = sqrt(R);

	ll ans = 0;
	if (s2 >= s1) {
		ans += s2 - s1 + 1;
	}
	ans += between(L, R);
	return ans;
}

int main() {
	int N;
	preprocess();
	scanf("%d", &N);
	FOR(q, N) {
		ll L, R;
		scanf("%I64d %I64d", &L, &R);
		printf("%I64d\n", query(L, R));
	}
	return 0;
}