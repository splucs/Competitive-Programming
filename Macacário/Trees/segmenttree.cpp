#include <cstdio>
#include <vector>
#include <algorithm>
#define INF (1<<30)
using namespace std;

/*
 * Segment Tree
 */

const int neutral = 0;
#define comp(a, b) ((a)+(b))

class SegmentTree {
	vector<int> a;
	int n;
public:
	SegmentTree(int* st, int* en) {
		int sz = int(en-st);
		for (n = 1; n < sz; n <<= 1);
		a.assign(n << 1, neutral);
		for(int i=0; i<sz; i++) a[i+n] = st[i];
		for(int i=n+sz-1; i; i--)
			a[i>>1] = comp(a[i>>1], a[i]);
	}
	void update(int i, int x) {
		a[i += n] = x; //substitui
		for (i >>= 1; i; i >>= 1)
			a[i] = comp(a[i<<1], a[1+(i<<1)]);
	}
	int query(int l, int r) {
		int ans = neutral;
		for (l += n, r += n+1; l < r; l >>= 1, r >>= 1) {
			if (l & 1) ans = comp(ans, a[l++]);
			if (r & 1) ans = comp(ans, a[--r]);
		}
		return ans;
	}
};

/*
 * TEST MATRIX
 */

int vet[16];

int main() {
	int n;
	scanf("%d", &n);
	for(int i=0; i<n; i++) scanf("%d", &vet[i]);
	char c;
	int a, b;
	SegmentTree st(vet, vet+n);
	while(scanf(" %c", &c), c=='u' || c=='s' ) {
		if (c == 'u') {
			scanf("%d %d", &a, &b);
			st.update(a, b);
		}
		else {
			scanf("%d %d", &a, &b);
			printf("soma(%d,%d)=%d\n", a, b, st.query(a, b));
		}
	}
	return 0;
}