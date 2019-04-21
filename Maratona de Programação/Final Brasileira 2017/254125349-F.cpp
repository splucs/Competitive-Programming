#include <bits/stdc++.h>
using namespace std;
#define MAXN 400009
#define MOD 1000000007
#define X first
#define Y second
typedef pair<int, int> ii;
typedef long long ll;

pair<ii, int> pos[MAXN];
map<int, int> occur;
ll acum[MAXN];

map<ii, ll> solutions;

const ll neutral = 0LL;
ll comp(ll a, ll b) {
	return max(a, b);
}

class SegmentTree {
private:
	vector<long long> st, pos;
	int size;
#define parent(p) (p >> 1)
#define left(p) (p << 1)
#define right(p) ((p << 1) + 1)
	void build(int p, int l, int r, ll * A) {
		if (l == r) {
			st[p] = A[l];
			pos[l] = p;
		}
		else {
			build(left(p), l, (l+r)/2, A);
			build(right(p), (l+r)/2+1, r, A);
			st[p] = comp(st[left(p)], st[right(p)]);
		}
	}
	ll find(int p, int l, int r, int a, int b) {
		if (a > r || b < l) return neutral;
		if (l >= a && r <= b) return st[p];
		
		ll p1 = find(left(p), l, (l+r)/2, a, b);
		ll p2 = find(right(p), (l+r)/2+1, r, a, b);
		return comp(p1, p2);
	}
public:
	SegmentTree(ll * begin, ll *end) {
		size = (int)(end-begin);
		st.assign(4*size, neutral);
		pos.assign(size + 9, 0);
		build(1, 0, size-1, begin);
	}
	ll query (int a, int b) { return find(1, 0, size-1, a, b); }
	
	void update(int n, ll num) {
		st[pos[n]] = num;
		n = parent(pos[n]);
		while(n > 0) {
			st[n] = comp(st[left(n)], st[right(n)]);
			n = parent(n);
		}
	}
};

int main() {
	int n = 0, a, b, c;
	map<int, int> occur;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d %d %d", &a, &b, &c);
		occur[a]++; occur[b]++;
		pos[i].first.X = a; pos[i].first.Y = b; pos[i].second = c;
	}
	
	int cnt = 1;
	for (map<int,int>::iterator it = occur.begin(); it != occur.end(); it++) {
		it->second = cnt++;
	}
	for (int i = 0; i < n; i++) {
		pos[i].first.X = occur[pos[i].first.X];
		pos[i].first.Y = occur[pos[i].first.Y];
	}
	
	sort(pos, pos + n);
	long long ans = 0; int lastAdded = -1;
	ll m;
	SegmentTree st(acum, acum + cnt + 9);
	
	for (int i = 0; i < n; i++) {
		if (i > 0 && pos[i].first.X != pos[i-1].first.X) {
			for (int k = lastAdded+1; k < i; k++) {
				st.update(pos[k].first.Y, acum[k]); 
			}
			lastAdded = i-1;
		}
		if (solutions.find(ii(pos[i].first.X, pos[i].first.Y)) != solutions.end()) {
			m = pos[i].second + solutions[ii(pos[i].first.X, pos[i].first.Y)];
		} else m = pos[i].second + st.query(0, pos[i].first.Y-1);
		
		solutions[ii(pos[i].first.X, pos[i].first.Y)] = m;
		ans = max(ans, m);
		acum[i] = m;
	}
	printf("%lld\n", ans);
	return 0;
}
