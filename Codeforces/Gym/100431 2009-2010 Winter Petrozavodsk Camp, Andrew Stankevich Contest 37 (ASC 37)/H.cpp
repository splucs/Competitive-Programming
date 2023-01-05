#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define MAXC 12
#define MAXLOGN 20
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define sz(x) int(x.size())
#define all(x) x.begin(),x.end()
#define mset(x, y) memset(&x, y, sizeof x)
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;

ll ceil(ll a, ll b) {
	assert(b != 0);
	if (a%b == 0) return a/b;
	return 1 + a/b;
}

int ans[MAXN];

struct ship {
	int type, id;
	ll t, w;
};

bool operator < (ship a, ship b) {
	if (a.t != b.t) return a.t < b.t;
	return a.id < b.id;
}

struct crane {
	int mask, id;
	ll t, v;
};

bool operator < (crane a, crane b) {
	if (a.t != b.t) return a.t < b.t;
	return a.id < b.id;
}

set<crane> idle[MAXC];
set<ship> docks[MAXC];

const int IDLE = 0;
const int ARRIVAL = 1;

struct event {
	int type;
	ll t;
	crane cr;
	ship sp;
};

set<event> events;

bool operator < (event a, event b) {
	if (a.t != b.t) return a.t < b.t;
	if (a.type != b.type) {
		return (a.type == ARRIVAL);
	}
	if (a.type == ARRIVAL) return a.sp < b.sp;
	if (a.type == IDLE) return a.cr < b.cr;
}

void becomeIdle(crane cr, ll t) {
	cr.t = t;
	ship sp; sp.t = INF;
	FOR(i, MAXC) {
		if (!(cr.mask & (1<<i))) continue;
		if (docks[i].empty()) continue;
		sp = min(sp, *docks[i].begin());
	}

	if (sp.t == INF) { //I became idle, no new ships at docks
		FOR(i, MAXC) {
			if (cr.mask & (1<<i)) idle[i].insert(cr);
		}
	}
	else { //new work to do
		int i = sp.type;
		docks[i].erase(sp);
		ans[sp.id] = cr.id;
		event ev;
		ev.type = IDLE;
		ev.t = cr.t = t + ceil(sp.w, cr.v);
		ev.cr = cr;
		events.insert(ev);
	}
}

void arrive(ship sp, ll t) {
	int i = sp.type;
	if (!idle[i].empty()) { //a crane can unload me
		crane cr = *idle[i].begin();
		FOR(j, MAXC) {
			if (cr.mask & (1<<j)) idle[j].erase(cr);
		}
		ans[sp.id] = cr.id;
		event ev;
		ev.type = IDLE;
		ev.t = cr.t = t + ceil(sp.w, cr.v);
		ev.cr = cr;
		events.insert(ev);
	}
	else { //I go to the docks
		docks[i].insert(sp);
	}
}

int main() {
	#ifdef ONLINE_JUDGE
	freopen("seaport.in", "r", stdin);
	freopen("seaport.out", "w", stdout);
	#endif

	int n, m, c;
	while(scanf("%d %d %d", &n, &m, &c) != EOF) {
		FOR(i, MAXC) idle[i].clear(), docks[i].clear();

		events.clear();
		FOR1(i, n) {
			ship sp;
			sp.id = i;
			scanf("%lld %d %lld", &sp.t, &sp.type, &sp.w);
			event ev;
			ev.type = ARRIVAL;
			ev.sp = sp;
			ev.t = sp.t;
			events.insert(ev);
		}
		FOR1(i, m) {
			crane cr;
			cr.id = i;
			int k, c;
			cr.t = -1;
			cr.mask = 0;
			scanf("%lld %d", &cr.v, &k);
			while(k --> 0) {
				scanf("%d", &c);
				cr.mask |= (1<<c);
			}
			event ev;
			ev.type = IDLE;
			ev.cr = cr;
			ev.t = cr.t;
			events.insert(ev);
		}

		while(!events.empty()) {
			event ev = *events.begin();
			events.erase(ev);
			if (ev.type == IDLE) becomeIdle(ev.cr, ev.t);
			if (ev.type == ARRIVAL) arrive(ev.sp, ev.t);
		}

		FOR1(i, n) printf("%d\n", ans[i]);
	}
	return 0;
}
