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
#define ub upper_bound
#define lb lower_bound
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;

ll modExp(ll a, ll b, ll m) {
	if (b == 0) return 1;
	ll c = modExp(a, b/2, m);
	c = (c*c) % m;
	if (b % 2 != 0) c = (c*a) % m;
	return c;
}

struct node {
	int l, r;
	ll x;
	node(int _l, int _r, ll _x) :
		l(_l), r(_r), x(_x) {}
};

bool operator < (node a, node b) {
	return a.l < b.l;
}

class IntervalTree {
	set<node> tree;
	set<node>::iterator it;
	void split(int i) {
		it = --tree.upper_bound(node(i, i, 0));
		if (it->l < i && it->r >= i) {
			node n1 = node(i, it->r, it->x);
			node n2 = *it;
			n2.r = i-1;
			tree.erase(it);
			tree.insert(n1);
			tree.insert(n2);
		}
	}
public:
	IntervalTree(int n) {
		tree.insert(node(0, n-1, 0));
	}
	IntervalTree(ll *st, ll *en) {
		for(int i = 0; st+i != en; i++) {
			tree.insert(node(i, i, st[i]));
		}
	}
	void add(int l, int r, ll x) {
		split(l); split(r+1);
		it = tree.lower_bound(node(l, l, 0));
		while(it != tree.end() && it->l <= r) {
			node n = *it;
			n.x += x;
			it = tree.erase(it);
			tree.insert(n);
		}
	}
	void set(int l, int r, ll x) {
		split(l); split(r+1);
		it = tree.lower_bound(node(l, l, 0));
		while(it != tree.end() && it->l <= r) {
			it = tree.erase(it);
		}
		tree.insert(node(l, r, x));
	}
	ll pw(int l, int r, ll p, ll m) {
		split(l); split(r+1);
		ll ans = 0, cur;
		it = tree.lower_bound(node(l, l, 0));
		while(it != tree.end() && it->l <= r) {
			cur = ((it->r - it->l + 1)*modExp(it->x % m, p, m)) % m;
			ans = (ans + cur) % m;
			it++;
		}
		return ans;
	}
	ll nth(int l, int r, int k) {
		split(l); split(r+1);
		map<ll, int> cnt;
		it = tree.lower_bound(node(l, l, 0));
		while (it != tree.end() && it->l <= r) {
			cnt[it->x] += it->r - it->l + 1;
			it++;
		}
		while (!cnt.empty() && k > 0) {
			int d = min(k, cnt.begin()->second);
			k -= d; cnt.begin()->second -= d;
			if (cnt.begin()->second == 0) {
				cnt.erase(cnt.begin());
			}
		}
		return cnt.begin()->first;
	}
};

int n, m;
ll seed, vmax;
ll a[MAXN];

int rnd() {
	int ret = seed;
	seed = (seed*7 + 13) % MOD;
	return ret;
}

int main() {
	scanf("%d %d %I64d %I64d", &n, &m, &seed, &vmax);
	FOR(i, n) a[i] = (rnd() % vmax) + 1;
	IntervalTree it(a, a+n);
	FOR(j, m) {
		int op = (rnd() % 4) + 1;
		int l = (rnd() % n);
		int r = (rnd() % n);
		if (l > r) swap(l, r);
		ll x;
		if (op == 3) {
			x = (rnd() % (r-l+1)) + 1;
		}
		else {
			x = (rnd() % vmax) + 1;
		}
		ll y;
		if (op == 4) {
			y = (rnd() % vmax) + 1;
		}

		switch(op) {
			case 1:
				it.add(l, r, x);
				break;
			case 2:
				it.set(l, r, x);
				break;
			case 3:
				printf("%I64d\n", it.nth(l, r, x-1));
				break;
			case 4:
				printf("%I64d\n", it.pw(l, r, x, y));
				break;
		}
	}
	return 0;
}