#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
#define MAXM 320
#define MOD 1000000007
#define INF 1000000009
#define EPS 1e-7
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define pb push_back
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;

int Lcmp;
bool Less(int i) { return i <= Lcmp; }

class WaveletTree {
private:
	vector<vector<int> > ml;
	vector<int> mt, arr; 
	int sig, size;
#define parent(p) (p >> 1)
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
		int p = (int)(stable_partition(A+l, A+r+1, Less) - A);
		build(left(u), l, p-1, lo, mid, A);
		build(right(u), p, r, mid+1, hi, A);
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
	
	int range(int i, int j, int a, int b) { return range(1, 0, sig, i, j+1, a, b); }
};

int a[MAXN], N;

int main() {
	scanf("%d", &N);
	FOR(i, N) {
		scanf("%d", &a[i]);
		a[i] = min(a[i], N);
		a[i]--;
	}
	WaveletTree wt(a, a+N, N);
	ll ans = 0;
	FOR(i, N) {
		int cur =  wt.range(0, a[i], i, N-1);
		if (a[i] >= i) cur--;
		ans += cur;
	}
	printf("%I64d\n", ans / 2);
	return 0;
}

