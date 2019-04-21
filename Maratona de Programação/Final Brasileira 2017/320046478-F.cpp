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

const ll neutral = 0;

class SegmentTree {
private:
	vector<long long> st, pos;
	int size;
#define parent(p) (p >> 1)
#define left(p) (p << 1)
#define right(p) ((p << 1) + 1)
	void build(int p, int l, int r) {
		if (l == r) {
			st[p] = neutral;
			pos[l] = p;
		}
		else {
			build(left(p), l, (l+r)/2);
			build(right(p), (l+r)/2+1, r);
			st[p] = max(st[left(p)], st[right(p)]);
		}
	}
	ll find(int p, int l, int r, int a, int b) {
		if (a > r || b < l) return neutral;
		if (l >= a && r <= b) return st[p];
		
		ll p1 = find(left(p), l, (l+r)/2, a, b);
		ll p2 = find(right(p), (l+r)/2+1, r, a, b);
		return max(p1, p2);
	}
public:
	SegmentTree() {}
	SegmentTree(int _sz) {
		size = _sz;
		st.assign(4*size, neutral);
		pos.assign(size + 9, 0);
		build(1, 0, size-1);
	}
	ll query (int a, int b) {
		if (b < a) return 0;
		ll ans = find(1, 0, size-1, a, b);
		//printf("query(%d,%d) = %lld\n", a, b, ans);
		return ans;
	}
	
	void update(int n, ll num) {
		st[pos[n]] = num;
		n = parent(pos[n]);
		while(n > 0) {
			st[n] = max(st[left(n)], st[right(n)]);
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
	ll ans = 0; int lastAdded = -1;
	ll cur;
	SegmentTree st(cnt+9);
	
	for (int i = 0; i < n; i++) {
		if (i > 0 && pos[i].first.X != pos[i-1].first.X) {
			for (int k = lastAdded+1; k < i; k++) {
				st.update(pos[k].first.Y, acum[k]); 
			}
			lastAdded = i-1;
		}
		if (i > 0 && pos[i].first.X == pos[i-1].first.X && pos[i].first.Y == pos[i-1].first.Y) {
			cur = pos[i].second + acum[i-1];
		}
		else cur = pos[i].second + st.query(0, pos[i].first.Y-1);
		//printf("%d,%d->%lld\n", pos[i].first.X, pos[i].first.Y, cur);
		
		//st.update(pos[i].first.Y, cur);
		ans = max(ans, cur);
		acum[i] = cur;
	}
	printf("%lld\n", ans);
	return 0;
}
