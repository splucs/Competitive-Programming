#include <cstdio>
#include <vector>
#include <algorithm>
#define MAXN 100009
#define INF (1<<30)

using namespace std;

const int neutral = INF;
int comp(int a, int b){
	return min(a, b);
}

class SegmentTree{
	private:
	vector<int> st, pos, lazy;
	int size;
	#define parent(p) (p>>1)
	#define left(p) (p<<1)
	#define right(p) ((p<<1)+1)
	void build(int p, int l, int r, int * A){
		if (l == r){
			st[p] = A[l]; pos[l] = p;
		}
		else{
			build(left(p), l, (l+r)/2, A);
			build(right(p), (l+r)/2+1, r, A);
			st[p] = comp(st[left(p)],st[right(p)]);
		}
	}
	void push(int p, int l, int r){
		st[p] += lazy[p];
		if (l!=r){
			lazy[right(p)] += lazy[p];
			lazy[left(p)] += lazy[p];
		}
		lazy[p] = 0;
	}
	void update(int p, int l, int r, int a, int b, int k){
		push(p, l, r);
		if (a>r || b < l) return;
		else if (l >=a && r<= b){
			lazy[p] = k; push(p, l, r);
		}
		else{
			update(left(p), l, (l+r)/2, a, b, k);
			update(right(p), (l+r)/2+1, r, a, b, k);
			st[p] = comp(st[left(p)],st[right(p)]);
		}
	}
	int query(int p, int l, int r, int a, int b){
		push(p, l, r);
		if (a>r || b<l) return neutral;
		if (l >=a && r<= b) return st[p];
		int p1 = query(left(p), l, (l+r)/2, a, b);
		int p2 = query(right(p), (l+r)/2+1, r, a, b);
		return comp(p1, p2);
	}
	public:
	SegmentTree(int* begin, int* end){
		size = (int)(end-begin);
		st.assign(4*size, 0);
		lazy.assign(4*size, 0);
		pos.assign(size+9, 0);
		build(1, 0, size-1, begin);
	}
	int query(int a, int b){
		return query(1, 0, size-1, a, b);
	}
	void update(int a, int b, int k){
		update(1, 0, size-1, a, b, k);
	}
};

int vet[MAXN], A[MAXN];

bool cmp(int a, int b){
	if (vet[a] == vet[b]) return b>a;
	if (vet[a] < vet[b]) return false;
	else return true;
}

int main(){
	int N, K;
	scanf("%d %d", &N, &K);
	for(int i=0; i<N; i++){
		A[i] = i;
		scanf("%d", &vet[i]);
	}
	SegmentTree st(A, A+N);
	sort(A, A+N, &cmp);
	for(int i=0; i<N; i++){
		if (st.query(A[i], N-1) < K) continue;
		if (A[i]+1<N && st.query(A[i]+1, N-1) <= K) continue;
		vet[A[i]] = 0;
		st.update(A[i], N-1, -K);
		if(A[i]+1<N) st.update(A[i]+1, N-1, -1);
	}
	int ans = 0;
	for(int i=0; i<N; i++){
		ans += vet[i];
	}
	printf("%d\n", ans);
	return 0;
}
