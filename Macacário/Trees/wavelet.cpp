#include <vector>
#include <algorithm>
using namespace std;

int Lcmp;
bool less(int i) { return i <= Lcmp; }

class WaveletTree {
private:
	vector< vector<int> > ml;
	vector<int> arr; 
	int sig, size;
#define left(p) (p << 1)
#define right(p) ((p << 1) + 1)
	
	void build(int u, int l, int r, int lo, int hi, int* A) {
		if (lo == hi) return;
		int mid = (lo + hi) / 2;
		Lcmp = mid;
		ml[u].reserve(r-l+2);
		ml[u].push_back(0);
		for (int i=l; i<=r; i++) {
			ml[u].push_back(ml[u].back() + (A[i]<=Lcmp));
		}
		int p = (int)(stable_partition(A+l, A+r+1, less) - A);
		build(left(u), l, p-1, lo, mid, A);
		build(right(u), p, r, mid+1, hi, A);
	}
	
	int rank(int u, int lo, int hi, int q, int i) {
		if (lo == hi) return i;
		int mid = (lo + hi) / 2, ri = ml[u][i];
		if (q <= mid) return rank(left(u), lo, mid, q, ri);
		else return rank(right(u), mid+1, hi, q, i - ri);
	}
	
	int quantile(int u, int lo, int hi, int i, int j, int k) {
		if (lo == hi) return lo;
		int mid = (lo + hi) / 2;
		int ri = ml[u][i-1], rj = ml[u][j], c = rj - ri;
		if (k <= c) return quantile(left(u), lo, mid, ri+1, rj, k);
		else return quantile(right(u), mid+1, hi, i-ri, j-rj, k-c);
	}
	
	int range(int u, int lo, int hi, int i, int j, int a, int b) {
		if (lo > b || hi < a) return 0;
		if (b >= hi && lo >= a) return j-i;
		int mid = (lo + hi) / 2;
		int ri = ml[u][i], rj = ml[u][j];
		int c1 = range(left(u), lo, mid, ri, rj, a, b);
		int c2 = range(right(u), mid+1, hi, i-ri, j-rj, a, b);
		return c1 + c2;
	}
	
	void swap(int u, int lo, int hi, int v1, int v2, int i) {
		if (lo == hi) return;
		int mid = (lo + hi) / 2;
		if (v1 <= mid) {
			if (v2 > mid) ml[u][i]--;
			else swap(left(u), lo, mid, v1, v2, ml[u][i]);
		}
		else {
			if (v2 <= mid) ml[u][i]++;
			else swap(right(u), mid+1, hi, v1, v2, i-ml[u][i]);			
		}
	}
	
public:
	WaveletTree() {}
	WaveletTree(int* begin, int* end, int _sig) {
		sig = _sig;
		size = (int)(end-begin);
		ml.resize(4*size);
		arr = vector<int>(begin, end);
		build(1, 0, size-1, 0, sig, &arr[0]);
		arr = vector<int>(begin, end);
	}
	
	int rank(int i, int q) { return rank(1, 0, sig, q, i+1); }
	int rank(int i, int j, int q) { return rank(j, q) - rank(i-1, q); }
	int quantile(int i, int j, int k) { return quantile(1, 0, sig, i+1, j+1, k); }
	int range(int i, int j, int a, int b) { return range(1, 0, sig, i, j+1, a, b); }
	void swap(int i) {
		if (i >= size-1) return;
		swap(1, 0, sig, arr[i], arr[i+1], i+1);
		std::swap(arr[i], arr[i+1]);
	}
};

/*
 * TEST MATRIX
 */

#include <cstdio>
#define DEBUG false
int testarr[100009];
WaveletTree wt;

bool test(int N, int sig, int nTest) {
	for(int t = 1; t <= nTest; t++) {
		if (DEBUG) printf("test array:");
		for(int i=0; i<N; i++) {
			testarr[i] = rand()%(sig+1);
			if (DEBUG) printf(" %d", testarr[i]);
		}
		if (DEBUG) printf("\n");
		
		if (DEBUG) printf("building Wavelet Tree\n");
		wt = WaveletTree(testarr, testarr+N, sig);
		if (DEBUG) printf("Wavelet Tree built\n");
		
		for(int j=1; j<=nTest; j++) {
			
			//execute swaps
			for(int s=0; s<nTest; s++) {
				int i = rand()%(N-1);
				swap(testarr[i], testarr[i+1]);
				wt.swap(i);
			}
			
			//test rank
			int a = rand()%N;
			int b = rand()%N;
			int q = rand()%(sig+1);
			if (a > b) swap(a, b);
			int ans = 0;
			if (DEBUG) printf("testarr[%d,%d]:", a, b);
			for(int i=a; i<=b; i++) {
				if (DEBUG) printf(" %d", testarr[i]);
				if (testarr[i] == q) ans++;
			}
			int wans = wt.rank(a, b, q);
			if (DEBUG) printf(" ans = %d wans = %d\n", ans, wans);
			if (ans != wans) {
				printf("Failed on rank test %d, rank(%d,%d,%d), ans = %d, wans = %d\n", j, a, b, q, ans, wans);
				return false;
			}
		
			//test quantile
			a = rand()%N;
			b = rand()%N;
			if (a > b) swap(a, b);
			int n = b-a+1;
			int k = 1 + rand()%n;
			vector<int> st(&testarr[a], &testarr[b] + 1);
			sort(st.begin(), st.end());
			if (DEBUG) printf("testarr[%d,%d]:", a, b);
			for(int i=0; i<n; i++) {
				if (DEBUG) printf(" %d", st[i]);
			}
			ans = st[k-1];
			wans = wt.quantile(a, b, k);
			if (DEBUG) printf(" ans = %d wans = %d\n", ans, wans);
			if (ans != wans) {
				printf("Failed on quantile test %d, quantile(%d,%d,%d), ans = %d, wans = %d\n", j, a, b, k, ans, wans);
				return false;
			}
			
			//test range
			a = rand()%N;
			b = rand()%N;
			if (a > b) swap(a, b);
			int l = rand()%(sig+1);
			int r = rand()%(sig+1);
			if (l > r) swap(l, r);
			if (DEBUG) printf("testarr[%d,%d]:", a, b);
			ans = 0;
			for(int i=a; i<=b; i++) {
				if (DEBUG) printf(" %d", testarr[i]);
				if (testarr[i] >= l && testarr[i] <= r) ans++;
			}
			wans = wt.range(a, b, l, r);
			if (DEBUG) printf(" ans = %d wans = %d\n", ans, wans);
			if (ans != wans) {
				printf("Failed on range test %d, range(%d,%d,%d,%d), ans = %d, wans = %d\n", j, a, b, l, r, ans, wans);
				return false;
			}
		}
	}
	printf("all tests passed\n");
	return true;
}

int main() {
	test(1000, 25, 100);
	return 0;
}

/*
 * SPOJ ILKQUERY
 */

/*#include <cstdio>
#define MAXN 100009
#include <map>
map<int, int> x2id;
int id2x[MAXN], arr[MAXN];

int main() {
	int N, Q;
	scanf("%d %d", &N, &Q);
	for(int i=0; i<N; i++) {
		scanf("%d", &arr[i]);
		x2id[arr[i]] = 0;
	}
	
	int sig = -1;
	for(map<int, int>::iterator it = x2id.begin(); it != x2id.end(); it++) {
		it->second = ++sig;
		id2x[it->second] = it->first;
	}
	for(int i=0; i<N; i++) arr[i] = x2id[arr[i]];
	
	WaveletTree wt(arr, arr+N, sig);
	
	int k, i, l;
	while(Q-->0) {
		scanf("%d %d %d", &k, &i, &l);
		int el = wt.quantile(0, i, k);
		//printf("%d-th element in [%d,%d] is %d\n", k, 0, i, id2x[el]);
		if (wt.rank(N-1, el) < l) {
			printf("-1\n");
			continue;
		}
		int lo = -1;
		int hi = N;
		while(hi > lo + 1) {
			int mid = (hi + lo) / 2;
			if (wt.rank(mid, el) < l) lo = mid;
			else hi = mid;
		}
		printf("%d\n", hi);
	}
	return 0;
}*/

/*
 * SPOJ ILKQUERYIII
 */

/*#define MAXN 1000009
#include <map>
#include <cstdio>
map<int, int> x2id;
int id2x[MAXN], arr[MAXN];

int main() {
	int N, Q;
	scanf("%d %d", &N, &Q);
	for(int i=0; i<N; i++) {
		scanf("%d", &arr[i]);
		x2id[arr[i]] = 0;
	}
	
	int sig = -1;
	for(map<int, int>::iterator it = x2id.begin(); it != x2id.end(); it++) {
		it->second = ++sig;
		id2x[it->second] = it->first;
	}
	for(int i=0; i<N; i++) arr[i] = x2id[arr[i]];
	
	WaveletTree wt(arr, arr+N, sig);
	
	int k, i, l, t;
	while(Q-->0) {
		scanf("%d", &t);
		if (t == 0) {
			scanf("%d %d %d", &i, &l, &k);
			int el = wt.quantile(0, i, k);
			//printf("%d-th element in [%d,%d] is %d\n", k, 0, i, id2x[el]);
			if (wt.rank(N-1, el) < l) {
				printf("-1\n");
				continue;
			}
			int lo = -1;
			int hi = N;
			while(hi > lo + 1) {
				int mid = (hi + lo) / 2;
				if (wt.rank(mid, el) < l) lo = mid;
				else hi = mid;
			}
			printf("%d\n", hi);
		}
		else {
			scanf("%d", &i);
			wt.swap(i);
		}
	}
	return 0;
}*/

