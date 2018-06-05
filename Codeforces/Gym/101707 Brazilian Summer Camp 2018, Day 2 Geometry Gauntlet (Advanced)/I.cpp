#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll nu, de;
struct line {
	ll m, b; bool is_query;
	mutable function<const line *()> succ;
	line(ll _m, ll _b, bool iq = false) :
		m(_m), b(_b), is_query(iq) {}
	bool operator<(const line &o) const {
		if (!o.is_query) return m < o.m;
		const line *s = succ();
		if (!s) return 0;
		return (b - s->b) * de < (s->m - m) * nu;
	}
};
 
struct HullDynamic : public multiset<line> {
	bool bad(iterator y) {
		auto z = next(y);
		if (y == begin()) {
			if (z == end()) return 0;
			return y->m == z->m && y->b <= z->b;
		}
		auto x = prev(y);
		if (z == end()) return y->m == x->m && y->b <= x->b;
		return (x->b - y->b) * (z->m - y->m) >= (y->b - z->b) * (y->m - x->m);
	}
	void insert_line(ll m, ll b) {
		auto y = insert(line(m, b));
		y->succ = [=] { return next(y) == end() ? 0 : &*next(y); };
		if (bad(y)) {
			erase(y); return;
		}
		while (next(y) != end() && bad(next(y))) erase(next(y));
		while (y != begin() && bad(prev(y))) erase(prev(y));
	}
	line query(ll a, ll b) {
		if (b < 0) a = -a, b = -b;
		nu = a; de = b;
		return *lower_bound(line(0, 0, true));
    }
};

/*
 * Codeforces 101707I
 */

#define MAXN 200309
#define MAXM 900009
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define EPS 1e-9
#define PI 3.141592653589793238462643383279502884
#define FOR(x,n) for(int x=0; (x)<int(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=int(n); (x)++)
#define REP(x,n) for(int x=int(n)-1; (x)>=0; (x)--)
#define REP1(x,n) for(int x=(n); (x)>0; (x)--)
#define pb push_back
#define pf push_front
#define fi first
#define se second
#define mp make_pair
#define all(x) x.begin(), x.end()
#define mset(x,y) memset(&x, (y), sizeof(x));
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef unsigned int uint;

char op[6];

int main() {
	int n, q;
	scanf("%d", &n);
	HullDynamic minhull, maxhull;
	ll minx = INF, maxx = -INF;
	FOR(i, n) {
		ll x, y;
		scanf("%lld %lld", &x, &y);
		minx = min(x, minx);
		maxx = max(x, maxx);
		maxhull.insert_line(x, y);
		minhull.insert_line(-x, -y);
	}
	scanf("%d", &q);
	while(q --> 0) {
		ll x, y, a, b;
		scanf(" %s", op);
		if (!strcmp(op, "add")) {
			scanf("%lld %lld", &x, &y);
			minx = min(x, minx);
			maxx = max(x, maxx);
			maxhull.insert_line(x, y);
			minhull.insert_line(-x, -y);
		}
		if (!strcmp(op, "get")) {
			scanf("%lld %lld", &a, &b);
			ll ans;
			if (b == 0) {
				if (a > 0) ans = maxx*a;
				else ans = minx*a;
			}
			else {
				line l(0, 0);
				if (b > 0) {
					l = maxhull.query(a, b);
					ans = a*l.m + b*l.b;
				}
				else {
					l = minhull.query(a, b);
					ans = -a*l.m + -b*l.b;
				}
			}
			printf("%lld\n", ans);
		}
	}
	return 0;
}