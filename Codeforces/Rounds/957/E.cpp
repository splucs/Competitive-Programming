#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
#define MAXM 320
#define MOD 1000000007
#define INF 1000000009
#define EPS 1e-9
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define pb push_back
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;

struct frac {
	ll x, y;
	frac(ll _x, ll _y) : x(_x), y(_y) {}
	double value() { return x*1.0/y; }
};

bool operator == (frac a, frac b) {
	return a.x*b.y == a.y*b.x;
}

bool operator < (frac a, frac b) {
	if (b.y*a.y < 0) return a.x*b.y > a.y*b.x;
	return a.x*b.y < a.y*b.x;
}

int bit1[MAXN], bit2[MAXN];
void update(int bit[], int i) {
	while(i < MAXN) {
		bit[i]++;
		i += (i&-i);
	}
}
int rsq(int bit[], int i) {
	int ans = 0;
	while (i > 0) {
		ans += bit[i];
		i -= (i&-i);
	}
	return ans;
}
int rsq(int bit[], int i, int j) {
	return rsq(bit, j) - rsq(bit, i-1);
}

int N, w;
typedef pair<frac, frac> line;
vector<line> lines;

int main() {

	scanf("%d %d", &N, &w);
	map<frac, int> x2id;

	FOR(i, N) {
		int x, v;
		scanf("%d %d", &x, &v);
		frac a = frac(1, x);
		frac b = frac(v, x);
		frac t1 = frac(v - w, x);
		frac t2 = frac(v + w, x);
		lines.pb(line(a, b));
		x2id[t1] = 0;
		x2id[t2] = 0;
	}

	sort(all(lines));
	int cnt = 0;
	for(auto & p : x2id) {
		p.second = ++cnt;
	}

	ll ans = 0;
	for(line l : lines) {
		frac a = l.first;
		frac b = l.second;
		ll v = b.x;
		ll x = b.y;
		frac t1 = frac(v - w, x);
		frac t2 = frac(v + w, x);
		int i1 = x2id[t1];
		int i2 = x2id[t2];
		int d1 = rsq(bit1, i1, cnt);
		int d2 = rsq(bit2, i2+1, cnt);
		//printf("line a=%.3f, t1=%.3f(%d), t2=%.3f(%d)\n", a.value(), t1.value(), i1, t2.value(), i2);
		ans += d1 - d2;
		update(bit1, i1);
		update(bit2, i2);
	}

	printf("%I64d\n", ans);
	return 0;
}