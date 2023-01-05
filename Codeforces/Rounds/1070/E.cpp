#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
#define MAXM 509
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define fi first
#define se second
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef pair<int, int> ii;

int n, m, a[MAXN], sz;
ll cnt[MAXN], sum[MAXN];
ll t;

void update(ll bit[], int i, int k) {
	for(; i <= n; i += (i&-i)) bit[i] += k;
}

ll rsq(ll bit[], int i) {
	ll sum = 0;
	for(; i; i -= (i&-i)) sum += bit[i];
	return sum;
}

ll rsq(ll bit[], int i, int j) {
	return rsq(bit, j) - rsq(bit, i-1);
}

void add(int i) {
	assert(1 <= i && i <= n);
	//printf("adding %d\n", i);
	sz++;
	update(cnt, i, 1);
	update(sum, i, a[i]);
}

int last(int k) {
	//printf("%d- lastest is ", k);
	assert(1 <= k && k <= sz);
	int lo = 0;
	int hi = n;
	k = sz-k+1;
	while(hi > lo + 1) {
		int mid = (hi + lo) / 2;
		int am = rsq(cnt, mid);
		if (am < k) lo = mid;
		else hi = mid;
	}
	//printf("%d\n", hi);
	return hi;
}

ll query() {
	if (sz == 0) return 0;
	int k = sz%m;
	if (k == 0) k = m;
	int i = last(k);
	ll ans = 2*rsq(sum, n) - rsq(sum, i, n);
	//printf("time required is %lld (%lld,%lld)\n", ans, rsq(sum, n), rsq(sum, i, n));
	return ans;
}

void remove() {
	int i = last(1);
	assert(1 <= i && i <= n);
	//printf("removing %d\n", i);
	sz--;
	update(cnt, i, -1);
	update(sum, i, -a[i]);
}

int main() {
	int T;
	scanf("%d", &T);
	FOR1(caseNo, T) {
		scanf("%d %d %lld", &n, &m, &t);

		FOR1(i, n) cnt[i] = sum[i] = 0;
		sz = 0;

		set<ii> pq;
		FOR1(i, n) {
			scanf("%d", &a[i]);
			pq.insert({a[i], i});
		}

		int ans = 0, ansd = 1;

		while(!pq.empty()) {
			int d = pq.begin()->fi;

			while(!pq.empty() && pq.begin()->fi == d) {
				add(pq.begin()->se);
				pq.erase(pq.begin());
			}

			while(query() > t) remove();
			if (d <= t && sz > ans) {
				ans = sz;
				ansd = d;
			}
		}
		printf("%d %d\n", ans, ansd);
	}
	return 0;
}