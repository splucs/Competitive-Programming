#include <vector>
using namespace std;
#define INF (1<<30)

const int neutral = INF;
int comp(int a, int b) {
	return min(a, b);
}

class SegmentTree {
	vector<int> a;
	int n;
public:
	SegmentTree(int* st, int* en) {
		int sz = int(en-st);
		for (n = 1; n < sz; n <<= 1);
		a.assign(n << 1, neutral);
		for(int i=0; i<sz; i++) a[i+n] = st[i];
		for(int i=n+sz-1; i>1; i--)
			a[i>>1] = comp(a[i>>1], a[i]);
	}
	void update(int i, int x) {
		a[i+n] = x; //substitui
		for (i += n, i >>= 1; i>1; i >>= 1)
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

#include <cstdio>
#define MAXN 100009
int arr[MAXN];

int main() {
	int T, N, Q;
	scanf("%d", &T);
	for(int t=1; t<=T; t++) {
		scanf("%d %d", &N, &Q);
		for(int i=0; i<N; i++) {
			scanf("%d", &arr[i]);
		}
		SegmentTree st(arr, arr+N);
		printf("Scenario #%d:\n", t);
		while(Q --> 0) {
			int i, j;
			scanf("%d %d", &i, &j);
			printf("%d\n", st.query(i-1, j-1));
		}
	}
	return 0;
}