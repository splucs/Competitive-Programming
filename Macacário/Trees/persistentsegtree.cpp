#include <vector>
#include <algorithm>
#define INF (1<<30)
using namespace std;
#define MAXS 2000009
#define MAXN 200009

/*
 * Persistent Segment Tree
 */

const int neutral = 0; //comp(x, neutral) = x
#define comp(a, b) ((a)+(b))

int nds, st[MAXS], ls[MAXS], rs[MAXS];

class PersistentSegmentTree {
private:
	int vroot[MAXN];
	int size, nds, nv;
	int newnode() {
		ls[nds] = rs[nds] = -1;
		st[nds++] = neutral;
		return nds-1;
	}
	void build(int p, int l, int r, int* A) {
		if (l == r) {
			st[p] = A ? A[l] : neutral;
			return;
		}
		int m = (l + r) / 2;
		build(ls[p] = newnode(), l, m, A);
		build(rs[p] = newnode(), m+1, r, A);
		st[p] = comp(st[ls[p]], st[rs[p]]);
	}
	void update(int prv, int p, int l, int r, int i, int k) {
		if (l == r) {
			st[p] = k; //substitui
			//st[p] = st[prv] + k; //agrega
			return;
		}
		int m = (l + r) / 2;
		if (i <= m) {
			rs[p] = rs[prv];
			update(ls[prv], ls[p] = newnode(), l, m, i, k);
		}
		else {
			ls[p] = ls[prv];
			update(rs[prv], rs[p] = newnode(), m+1, r, i, k);
		}
		st[p] = comp(st[ls[p]], st[rs[p]]);
	}
	int query(int p, int l, int r, int a, int b) {
		if (a > r || b < l) return neutral;
		if (l >= a && r <= b) return st[p];
		int m = (l + r) / 2;
		int p1 = query(ls[p], l, m, a, b);
		int p2 = query(rs[p], m + 1, r, a, b);
		return comp(p1, p2);
	}
public:
	PersistentSegmentTree(int* begin, int* end) {
		nds = nv = 0; size = (int)(end-begin);
		vroot[nv++] = newnode();
		build(vroot[0], 0, size-1, begin);
	}
	PersistentSegmentTree(int _size = 1) {
		nds = nv = 0; size = _size;
		vroot[nv++] = newnode();
		build(vroot[0], 0, size-1, NULL);
	}
	int query(int a, int b, int v) {
		return query(vroot[v], 0, size-1, a, b);
	}
	int update(int i, int v, int k) {
		vroot[nv++] = newnode();
		update(vroot[v], vroot[nv-1], 0, size-1, i, k);
		return nv-1;
	}
	int nver() { return nv; }
};

/*
 * TEST MATRIX
 */

#include <ctime>
#include <cstdio>
#define DEBUG false
const int N = 500;
int arr[N+9][N+9];
int curver;
PersistentSegmentTree pst;
bool test(int NTests) {
	srand(time(NULL));
	for(int nt=0; nt<NTests; nt++) {
		for(int i=0; i<N; i++) arr[0][i] = rand()%N;
		
		if(DEBUG) printf("building seg tree...\n");
		pst = PersistentSegmentTree(&arr[0][0], &arr[0][0] + N);
		curver = 1;
		if(DEBUG) printf("arr[%d]:", curver-1);
		for(int j=0; j<N; j++) {
			if(DEBUG) printf(" %2d", arr[curver-1][j]);
		}
		if(DEBUG) printf("\n");
		
		for(int i=0; i<N; i++) {
			if(DEBUG) printf("test %d:\n", i+1);
			
			// update
			int id = rand()%N;
			int k = rand()%N;
			int v = rand()%curver;
			if(DEBUG) printf("update over version %d: arr[%d] = %d\n", v, id, k);
			for(int j=0; j<N; j++) arr[curver][j] = arr[v][j];
			curver++;
			arr[curver-1][id] = k;
			if(DEBUG) printf("arr[%d]:", curver-1);
			for(int j=0; j<N; j++) {
				if(DEBUG) printf(" %2d", arr[curver-1][j]);
			}
			if(DEBUG) printf("\n");
			
			if (pst.update(id, v, k) != curver-1) {
				printf("failed to update at test %d\n", i+1);
				return false;
			}
			
			//queries over recent version
			for(int t=0; t<N; t++) {
				int a = rand()%N;
				int b = rand()%N;
				if (a > b) swap(a, b);
				int val1 = 0;
				for(int j=a; j<=b; j++) val1 = comp(val1, arr[curver-1][j]);
				int val2 = pst.query(a, b, curver-1);
				if(DEBUG) printf("sum[%d,%d] = %d (ver %d)\n", a, b, val1, curver-1);
				if (val1 != val2) {
					printf("failed at test %d, case %d (%d==%d), ver %d\n", i+1, t+1, val1, val2, curver-1);
					printf("arr[%d]:", curver-1);
					for(int j=0; j<N; j++) {
						printf(" %2d", arr[curver-1][j]);
					}
					printf("\nquery [%d,%d]\n", a, b);
					return false;
				}
			}
			
			//queries over all versions
			for(int t=0; t<N; t++) {
				int a = rand()%N;
				int b = rand()%N;
				int v = rand()%curver;
				if (a > b) swap(a, b);
				int val1 = 0;
				for(int j=a; j<=b; j++) val1 = comp(val1, arr[v][j]);
				int val2 = pst.query(a, b, v);
				if(DEBUG) printf("sum[%d,%d] = %d (ver %d)\n", a, b, val1, v);
				if (val1 != val2) {
					printf("failed at test %d, case %d (%d==%d), ver %d\n", i+1, t+1, val1, val2, v);
					printf("arr[%d]:", v);
					for(int j=0; j<N; j++) {
						printf(" %2d", arr[v][j]);
					}
					printf("\nquery [%d,%d]\n", a, b);
					return false;
				}
			}		
		}
	}
	printf("all tests passed\n");
	return true;
}

int main() {
	test(10);
	return 0;
}

/*
 * SPOJ DQUERY
 */

/*#define MAXN 100009
#include <cstdio>
#include <map>

int a[MAXN], id[MAXN], ver[MAXN];

bool cmp(int i, int j) {
	return a[i] < a[j];
}

PersistentSegmentTree pst(MAXN);

int main() {
	int N, Q, u, v, x;
	scanf("%d", &N);
	map<int, int> last;
	for(int i=0; i<N; i++) {
		scanf("%d", &x);
		if (last.count(x)) a[i] = last[x];
		else a[i] = -1;
		last[x] = i;
		id[i] = i;
	}
	sort(id, id+N, cmp);
	pst = PersistentSegmentTree(N);
	for(int it=0, i; it<N; it++) {
		i = id[it];
		ver[it] = pst.update(i, pst.nver()-1, pst.query(i, i, pst.nver()-1) + 1);
	}
	scanf("%d", &Q);
	while(Q-->0) {
		scanf("%d %d", &u, &v);
		int lo = -1;
		int hi = N;
		while(hi > lo+1) {
			int m = (hi+lo)/2;
			if (a[id[m]] < u-1) lo = m;
			else hi = m;
		}
		if (lo < 0) printf("0\n");
		else printf("%d\n", pst.query(u-1, v-1, ver[lo]));
	}
	return 0;
}*/