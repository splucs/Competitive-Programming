#include <cstdio>
#include <vector>
#include <algorithm>
#define INF (1<<30)
using namespace std;

const int neutral = 0;
int comp(int a, int b) {
	return a+b;
}

class SegmentTree {
private:
	vector<int> st, pos;
	int size;
#define parent(p) (p >> 1)
#define left(p) (p << 1)
#define right(p) ((p << 1) + 1)
	void build(int p, int l, int r, int* A) {
		if (l == r) {
			st[p] = A[l];
			pos[l] = p;
		}
		else {
			build(left(p), l, (l + r) / 2, A);
			build(right(p), (l + r) / 2 + 1, r, A);
			st[p] = comp(st[left(p)], st[right(p)]);
		}
	}
	int find(int p, int l, int r, int a, int b) {
		if (a > r || b < l) return neutral;
		if (l >= a && r <= b) return st[p];
		int p1 = find(left(p), l, (l + r) / 2, a, b);
		int p2 = find(right(p), (l + r) / 2 + 1, r, a, b);
		return comp(p1, p2);
	}
public:
	SegmentTree(int* begin, int* end) {
		size = (int)(end - begin);
		st.assign(4 * size, neutral);
		pos.assign(size + 9, 0);
		build(1, 0, size - 1, begin);
	}
	int query(int a, int b) { return find(1, 0, size - 1, a, b); }
	void update(int n, int num) {
		st[pos[n]] = num;
		n = parent(pos[n]);
		while (n>0) {
			st[n] = comp(st[left(n)], st[right(n)]);
			n = parent(n);
		}
	}
};

int vet[16];

int main(){
	int n;
	scanf("%d", &n);
	for(int i=0; i<n; i++) scanf("%d", &vet[i]);
	char c;
	int a, b;
	SegmentTree st(vet, vet+n);
	while(scanf(" %c", &c), c=='u' || c=='s' ){
		if (c == 'u'){
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