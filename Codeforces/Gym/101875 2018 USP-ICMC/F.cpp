#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < int(n); i++)
#define MAXN 100009
#define pb push_back
#define fi first
#define se second
#define all(x) x.begin(), x.end()
typedef vector<int> vi;
typedef long long ll;
typedef pair<int, int> ii;

void merge(set<ll> & a, set<ll> & b) {
	if (a.size() > b.size()) swap(a, b);
	vector<ll> toremove;
	for(ll x : a) {
		if (!b.count(x)) toremove.pb(x);
	}
	for(ll x : toremove) a.erase(x);
}

int main() {
	int n;
	scanf("%d", &n);
	set<ll> likes, hates;
	bool liked = false;
	FOR(i, n) {
		int t, k;
		scanf("%d %d", &t, &k);
		if (t == 1) {
			set<ll> cur;
			FOR(j, k) {
				ll x;
				scanf("%lld", &x);
				cur.insert(x);
			}
			if (!liked) {
				likes = cur;
				liked = true;
			}
			else merge(likes, cur);
		}
		else {
			FOR(j, k) {
				ll x;
				scanf("%lld", &x);
				hates.insert(x);
			}
		}
	}
	for(ll x : hates) likes.erase(x);
	ll ans = likes.size();
	if (!liked) ans = 1e18 - hates.size();
	printf("%lld\n", ans);
	return 0;
}