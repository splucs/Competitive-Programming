#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define pb push_back
#define all(x) x.begin(),x.end()
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
typedef long long ll;

struct hd {
	int from, to, delta;
	hd(int _from, int _to) : from(_from), to(_to) {
		delta = to - from;
	}
};

bool operator < (hd a, hd b) {
	if (a.delta < 0 && b.delta < 0) {
		return a.to > b.to;
	}
	if (a.delta >= 0 && b.delta >= 0) {
		return a.from < b.from;
	}
	return a.delta > b.delta;
}

bool check(ll X, vector<hd> &arr) {
	for(auto h : arr) {
		if (X < h.from) return false;
		X += h.delta;
	}
	return true;
}

int main() {
	vector<hd> arr;
	int n;
	scanf("%d", &n);
	FOR(i, n) {
		int from, to;
		scanf("%d %d", &from, &to);
		arr.pb(hd(from, to));
	}
	sort(all(arr));
	ll hi = INFLL;
	ll lo = 0;
	while(hi > lo + 1) {
		ll mid = (hi + lo) / 2;
		if (check(mid, arr)) hi = mid;
		else lo = mid;
	}
	printf("%lld\n", hi);
	return 0;
}