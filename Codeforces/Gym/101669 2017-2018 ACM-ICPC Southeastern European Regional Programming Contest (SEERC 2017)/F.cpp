#include <bits/stdc++.h>
#define MAXN 5009
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define fi first
#define se second
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
using namespace std;
typedef long long int ll;
typedef pair<int, int> ii;
typedef vector<int> vi;

multiset<ll> to[2][2];
char a[MAXN], b[MAXN];
int c[MAXN];
ll sum11;

ll simulate() {
	ll ans = 0;

	vector<ll> to10(all(to[1][0]));
	FOR(i, sz(to10)-1) {
		if (i > 0) to10[i] += to10[i-1];
		ans += to10[i];
	}

	vector<ll> to01(all(to[0][1]));
	FOR(i, sz(to01)) {
		if (i > 0) to01[i] += to01[i-1];
		ans += to01[i];
	}

	ans += (sz(to01) + sz(to10))*sum11;

	return ans;
}

int main() {
	int n;
	scanf("%d", &n);
	FOR(i, n) scanf("%d", &c[i]);
	scanf(" %s %s", a, b);
	FOR(i, n) {
		to[a[i]-'0'][b[i]-'0'].insert(c[i]);
	}

	sum11 = 0;
	for(ll x : to[1][1]) sum11 += x;
	
	ll ans = simulate();
	vector<ll> to11(all(to[1][1]));
	REP(i, sz(to11)) {
		ll x = to11[i];
		sum11 -= x;
		to[0][1].insert(x);
		to[1][0].insert(x);
		ans = min(ans, simulate());
	}
	assert(sum11 == 0);

	printf("%lld\n", ans);
	return 0;
}