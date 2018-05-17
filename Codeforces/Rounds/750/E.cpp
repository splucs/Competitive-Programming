#include <bits/stdc++.h>
using namespace std;
#define DEBUG false
#define debugf if (DEBUG) printf
#define MAXN 200309
#define MAXM 300009
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define EPS 1e-9
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define ROF(x,n) for(int x=(n)-1; (x)>=0; (x)--)
#define ROF1(x,n) for(int x=(n); (x)>0; (x)--)
#define pb push_back
#define pf push_front
#define fi first
#define se second
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;

struct matrix {
	int mat[5][5];
};

matrix mx2, mx1, mx0, mx7, mx6, mxdef, neutral;

matrix join(matrix a, matrix b) {
	matrix c = neutral;
	FOR(i, 5) FOR(j, 5) {
		if (i > j) continue;
		for(int k = i; k <= j; k++) {
			if (c.mat[i][j] > a.mat[i][k] + b.mat[k][j])
				c.mat[i][j] = a.mat[i][k] + b.mat[k][j];
		}
	}
	return c;
}

class SegmentTree {
	vector<matrix> arr;
	int n;
	#define left(p) (p<<1)
	#define right(p) (1+left(p))
	void build(int p, int l, int r, char *st) {
		if (l == r) {
			arr[p] = mxdef;
			if (st[r] == '2') arr[p] = mx2;
			if (st[r] == '0') arr[p] = mx0;
			if (st[r] == '1') arr[p] = mx1;
			if (st[r] == '7') arr[p] = mx7;
			if (st[r] == '6') arr[p] = mx6;
		}
		else {
			int m = (l+r)/2;
			build(left(p), l, m, st);
			build(right(p), m+1, r, st);
			arr[p] = join(arr[left(p)], arr[right(p)]);
		}
	}
	matrix query(int p, int l, int r, int a, int b) {
		if (b < l || a > r) return mxdef;
		if (l >= a && r <= b) {
			return arr[p];
		}
		int m = (l+r)/2;
		matrix p1 = query(left(p), l, m, a, b);
		matrix p2 = query(right(p), m+1, r, a, b);
		matrix ans = join(p1, p2);
		return ans;
	}
public:
	SegmentTree(char* st, int _n) {
		n = _n;
		arr.resize(4*n + 9, mxdef);
		build(1, 0, n-1, st);
	}
	matrix query(int a, int b) {
		return query(1, 0, n-1, a, b);
	}
};

char s[MAXN];

int main() {
	memset(&neutral.mat, INF, sizeof neutral.mat);

	mxdef = neutral;
	FOR(i, 5) mxdef.mat[i][i] = 0;

	mx2 = mxdef;
	mx2.mat[0][0] = 1;
	mx2.mat[0][1] = 0;
	mx0 = mxdef;
	mx0.mat[1][1] = 1;
	mx0.mat[1][2] = 0;
	mx1 = mxdef;
	mx1.mat[2][2] = 1;
	mx1.mat[2][3] = 0;
	mx7 = mxdef;
	mx7.mat[3][3] = 1;
	mx7.mat[3][4] = 0;
	mx6 = mxdef;
	mx6.mat[3][3] = 1;
	mx6.mat[4][4] = 1;

	int n, q;
	scanf("%d %d %s", &n, &q, s);
	SegmentTree st(s, n);
	while (q --> 0) {
		int a, b;
		scanf("%d %d", &a, &b);
		a--; b--;
		int ans = st.query(a, b).mat[0][4];
		if (ans >= INF) ans = -1;
		printf("%d\n", ans);
	}
	return 0;
}