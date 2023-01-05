#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009

class MergeSortTree { // the MergeSort tree is stored like a heap array
private:
	vector< vector<int> > st;
	int size;
	#define parent(p) (p >> 1)
	#define left(p) (p << 1)
	#define right(p) ((p << 1) + 1)
	void build(int p, int l, int r, int* A) { // O(n)
		st[p].resize(r-l+1);
		if (l == r){
			st[p][0] = A[l];
		}
		else {
			int pl = left(p), pr = right(p), m = (l+r)/2;
			build(pl , l, m, A);
			build(pr, m+1, r, A);
			unsigned int i=0, j=0, k=0;
			while(i < st[pl].size() && j < st[pr].size()){
				if (st[pl][i] < st[pr][j]) st[p][k++] = st[pl][i++];
				else st[p][k++] = st[pr][j++];
			}
			while(i < st[pl].size()) st[p][k++] = st[pl][i++];
			while(j < st[pr].size()) st[p][k++] = st[pr][j++];
		}
	}
	int less(int p, int l, int r, int a, int b, int k) { // O(log n)
		if (st[p][0] >= k || a > r || b < l) return 0;
		if (l >= a && r <= b){
			l = 0; r = (int)st[p].size();
			int m;
			while(r > l + 1){
				m = (r+l)/2;
				if (st[p][m] < k) l = m;
				else r = m;
			}
			return r;
		}
		int p1 = less(left(p), l, (l+r)/2, a, b, k);
		int p2 = less(right(p), (l+r)/2+1, r, a, b, k);
		return p1+p2;
	}
public:
	MergeSortTree() {}
	MergeSortTree(int* begin, int* end) {
		size = (int)(end-begin);
		st.assign(4*size, vector<int>());
		build(1, 0, size-1, begin);
	}
	int less(int a, int b, int k) {
		return less(1, 0, size-1, a, b, k);
	}
};

MergeSortTree mst;
int arr[MAXN];

typedef long long ll;

ll query(int x1, int x2, int y1, int y2) {
	x1--; x2--;
	ll n = mst.less(x1, x2, y2+1) - mst.less(x1, x2, y1);
	ll ans = n*(n-1)/2;
	//printf("query(%d,%d,%d,%d) = %I64d,%I64d\n", x1+1, x2+1, y1, y2, n, ans);
	return ans;
}

int main() {
	int N, Q;
	scanf("%d %d", &N, &Q);
	for(int i=1; i<=N; i++) {
		scanf("%d", &arr[i]);
	}
	mst = MergeSortTree(arr+1, arr+1+N);
	int x1, x2, y1, y2;
	while(Q-->0) {
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		ll ans = N*1LL*(N-1)/2;
		ans -= query(1, N, y2+1, N);
		ans -= query(1, N, 1, y1-1);
		ans -= query(1, x1-1, 1, N);
		ans -= query(x2+1, N, 1, N);
		ans += query(1, x1-1, 1, y1-1);
		ans += query(1, x1-1, y2+1, N);
		ans += query(x2+1, N, 1, y1-1);
		ans += query(x2+1, N, y2+1, N);
		printf("%I64d\n", ans);
	}
	return 0;
}