#include <cstdio>
#include <vector>
#include <algorithm>
#define INF (1<<30)
using namespace std;

const int neutral = 0; //comp(x, neutral) = x
int comp(int a, int b) {
	return a + b;
}

struct node{
	int sum, lazy, copy, left, right;
	node(int _sum, int _copy) : sum(_sum), lazy(0), copy(_copy), left(-1), right(-1) {}
}

class SegmentTree {
private:
	vector<int> version;
	vector<node> st;
	int size;
	int & left(int p) { return st[p].left; }
	int & right(int p) { return st[p].right; }
	int & lazy(int p) { return st[p].lazy; }
	void build(int p, int l, int r, int* A) {
		if (l == r) return;
		st[p].left = st.size();
		st.push_back(node(A[l]));
		build(left(p), l, (l + r) / 2, A);
		st[p].right = st.size();
		st.push_back(node(A[r]));
		build(right(p), (l + r) / 2 + 1, r, A);
		st[p].sum = comp(st[left(p)].sum, st[right(p)].sum);
	}
	void push(int p, int l, int r) {
		st[p].sum += (r - l + 1)*lazy(p);	//Caso RSQ
		//st[p].sum += st[p].lazy; 		    //Caso RMQ
		if (l != r) {
			lazy(right(p)) += lazy(p);
			lazy(left(p)) += lazy(p);
		}
		lazy(p) = 0;
	}
	void update(int p, int cp, int l, int r, int a, int b, int k) {
		push(p, l, r);
		if (a > r || b < l) return;
		else if (l >= a && r <= b) {
			lazy[p] = k; push(p, l, r);
		}
		else {
			update(left(p), l, (l + r) / 2, a, b, k);
			update(right(p), (l + r) / 2 + 1, r, a, b, k);
			st[p] = comp(st[left(p)], st[right(p)]);
		}
	}
	int query(int p, int l, int r, int a, int b) {
		push(p, l, r);
		if (a > r || b < l) return neutral;
		if (l >= a && r <= b) return st[p];
		int p1 = query(left(p), l, (l + r) / 2, a, b);
		int p2 = query(right(p), (l + r) / 2 + 1, r, a, b);
		return comp(p1, p2);
	}
public:
	SegmentTree(int* begin, int* end) {
		size = (int)(end - begin);
		st.assign(4 * size, neutral);
		lazy.assign(4 * size, 0);
		build(1, 0, size - 1, begin);
	}
	int query(int a, int b) { return query(1, 0, size - 1, a, b); }
	void update(int a, int b, int k) { update(1, 0, size - 1, a, b, k); }
};

int vet[16];

int main(){
	int n, k;
	scanf("%d", &n);
	for(int i=0; i<n; i++) scanf("%d", &vet[i]);
	char c;
	int a, b;
	SegmentTree st(vet, vet+n);
	while(scanf(" %c", &c), c=='u' || c=='s' ){
		if (c == 'u'){
			scanf("%d %d %d", &a, &b, &k);
			st.update(a, b, k);
		}
		else {
			scanf("%d %d", &a, &b);
			printf("soma(%d,%d)=%d\n", a, b, st.query(a, b));
		}
	}
	return 0;
}