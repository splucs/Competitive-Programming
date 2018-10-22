#include <bits/stdc++.h>
using namespace std;
#define MAXN 10009
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define fi first
#define se second
#define sz(x) int(x.size())
#define all(x) x.begin(),x.end()
#define mset(x, y) memset(&x, y, sizeof x)
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;

int basic[26][5][5] = {
	//A
	{{}},
	//B
	{{}},
	//C
	{{}},
	//D
	{{}},
	//E
	{{}},
	//F
	{
		{0, 1, 1},
		{1, 1, 0},
		{0, 1, 0}
	},
	//G
	{{}},
	//H
	{{}},
	//I
	{
		{1},
		{1},
		{1},
		{1},
		{1}
	},
	//J
	{{}},
	//K
	{{}},
	//L
	{
		{1, 0},
		{1, 0},
		{1, 0},
		{1, 1}
	},
	//M
	{{}},
	//N
	{
		{0, 1},
		{0, 1},
		{1, 1},
		{1, 0}
	},
	//O
	{{}},
	//P
	{
		{1, 1},
		{1, 1},
		{1, 0}
	},
	//Q
	{{}},
	//R
	{{}},
	//S
	{{}},
	//T
	{
		{1, 1, 1},
		{0, 1, 0},
		{0, 1, 0}
	},
	//U
	{
		{1, 0, 1},
		{1, 1, 1}
	},
	//V
	{
		{1, 0, 0},
		{1, 0, 0},
		{1, 1, 1}
	},
	//W
	{
		{1, 0, 0},
		{1, 1, 0},
		{0, 1, 1}
	},
	//X
	{
		{0, 1, 0},
		{1, 1, 1},
		{0, 1, 0}
	},
	//Y
	{
		{0, 1},
		{1, 1},
		{0, 1},
		{0, 1}
	},
	//Z
	{
		{1, 1, 0},
		{0, 1, 0},
		{0, 1, 1}
	},
};

struct shape {
	int a[5][5];
	shape(char c = 'B') {
		FOR(i, 5) FOR(j, 5) a[i][j] = basic[c-'A'][i][j];
	}
	void fix() {
		int si = 5, sj = 5;
		FOR(i, 5) FOR(j, 5) {
			if (!a[i][j]) continue;
			if (si > i) si = i;
			if (sj > j) sj = j;
		}
		FOR(i, 5) FOR(j, 5) {
			if (i < si || j < sj) continue;
			a[i-si][j-sj] = a[i][j];
			a[i][j] = 0;
		}
	}
	void rotate() {
		FOR(i, 3) FOR(j, 2) {
			int tmp = a[i][j];
			a[i][j] = a[j][4-i];
			a[j][4-i] = a[4-i][4-j];
			a[4-i][4-j] = a[4-j][i];
			a[4-j][i] = tmp;
		}
		fix();
	}
	void reverse() {
		FOR(i, 5) std::reverse(a[i], a[i] + 5);
		fix();
	}
};

pair<ll, ll> encode(shape &s, int di, int dj) {
	ll a1 = 0, a2 = 0;
	FOR(i, 5) FOR(j, 5) {
		if (!s.a[i][j]) continue;
		if (i+di < 5) {
			int n = 10*(i+di) + (j+dj);
			a1 |= (1LL<<n);
		}
		else {
			int n = 10*(i+di-5) + (j+dj);
			a2 |= (1LL<<n);
		}
	}
	return {a1, a2};
}

void print(ll a1, ll a2) {
	printf("\n");
	FOR(i, 10) {
		FOR(j, 10) {
			int bit = 0;
			if (i < 5) {
				int n = 10*(i) + (j);
				bit = (a1 & (1LL<<n)) != 0;
			}
			else {
				int n = 10*(i-5) + (j);
				bit = (a2 & (1LL<<n)) != 0;
			}
			printf("%d", bit);
		}
		printf("\n");
	}
}

bool join(shape &s1, int i1, int j1, shape &s2, int i2, int j2, ll &a1, ll &a2) {
	auto p1 = encode(s1, i1, j1);
	auto p2 = encode(s2, i2, j2);
	if (p1.fi & p2.fi) return false;
	if (p1.se & p2.se) return false;
	a1 = p1.fi | p2.fi;
	a2 = p1.se | p2.se;
	//print(a1, a2);
	return true;
}

vector<shape> getShapes(char c) {
	shape base(c);
	vector<shape> ans;
	FOR(i, 4) {
		base.reverse();
		ans.pb(base);
		base.reverse();
		base.rotate();
		ans.pb(base);
	}
	return ans;
}

set< pair<ll,ll> > codes(char s, char t) {
	auto vs = getShapes(s);
	auto vt = getShapes(t);
	set< pair<ll,ll> > ans;
	ll a1, a2;
	for(auto &s1 : vs) for(auto &s2 : vt) {
		FOR(i1, 5) FOR(j1, 5) FOR(i2, 5) FOR(j2, 5) {
			if(join(s1, i1, j1, s2, i2, j2, a1, a2)) {
				ans.insert({a1, a2});
			}
		}
	}
	return ans;
}

map< pair<char,char>, set< pair<ll,ll> > > pos;

bool valid(char c) {
	if (c == 'F') return true;
	if (c == 'I') return true;
	if (c == 'L') return true;
	if (c == 'N') return true;
	if (c == 'P') return true;
	if (c == 'T') return true;
	if (c == 'U') return true;
	if (c == 'V') return true;
	if (c == 'W') return true;
	if (c == 'X') return true;
	if (c == 'Y') return true;
	if (c == 'Z') return true;
	return false;
}

int main() {

	FOR(c1, 26) FOR(c2, 26) {
		if (!valid(c1+'A') || !valid(c2+'A')) continue;
		pos[{c1+'A',c2+'A'}] = codes(c1+'A',c2+'A');
	}

	char a, b, c, d;
	while(scanf(" %c %c %c %c", &a, &b, &c, &d) != EOF) {
		auto &s1 = pos[{a,b}];
		auto &s2 = pos[{c,d}];
		//auto s1 = codes(a, b);
		//auto s2 = codes(c, d);
		bool ok = false;
		assert(!s1.empty() && !s2.empty());
		for(auto p : s1) if (s2.count(p)) ok = true;
		printf("%s\n", ok ? "YES" : "NO");
	}
	return 0;
}