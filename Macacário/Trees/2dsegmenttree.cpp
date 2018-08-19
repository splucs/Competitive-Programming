#include <algorithm>
#include <vector>
using namespace std;
#define MAXM 100000009 //1e8+9
#define INF 0x3f3f3f3f

/*
 * 2D Segment Tree
 */

int rs[MAXM], ls[MAXM], st[MAXM], cnt = 0;

class SegmentTree2D {
	int sizex, sizey, v, root;
	int x, y, ix, jx, iy, jy;
	void updatex(int p, int lx, int rx) {
		if (x < lx || rx < x) return;
		st[p] += v;
		if (lx == rx) return;
		if (!rs[p]) rs[p] = ++cnt, ls[p] = ++cnt;
		int mx = (lx + rx) / 2;
		updatex(ls[p], lx, mx);
		updatex(rs[p], mx + 1, rx);
	}
	void updatey(int p, int ly, int ry) {
		if (y < ly || ry < y) return;
		if (!st[p]) st[p] = ++cnt;
		updatex(st[p], 0, sizex);
		if (ly == ry) return;
		if (!rs[p]) rs[p] = ++cnt, ls[p] = ++cnt;
		int my = (ly + ry) / 2;
		updatey(ls[p], ly, my);
		updatey(rs[p], my + 1, ry);
	}
	int queryx(int p, int lx, int rx) {
		if (!p || jx < lx || ix > rx) return 0;
		if (ix <= lx && rx <= jx) return st[p];
		int mx = (lx + rx) / 2;
		return queryx(ls[p], lx, mx) +
			queryx(rs[p], mx + 1, rx);
	}
	int queryy(int p, int ly, int ry) {
		if (!p || jy < ly || iy > ry) return 0;
		if (iy <= ly && ry <= jy) return queryx(st[p], 0, sizex);
		int my = (ly + ry) / 2;
		return queryy(ls[p], ly, my) +
			queryy(rs[p], my + 1, ry);
	}
public:
	SegmentTree2D(int nx, int ny) : sizex(nx), sizey(ny) {
		root = ++cnt;
	}
	void update(int _x, int _y, int _v) {
		x = _x; y = _y; v = _v;
		updatey(root, 0, sizey);
	}
	int query(int _ix, int _jx, int _iy, int _jy) {
		ix = _ix; jx = _jx; iy = _iy; jy = _jy;
		return queryy(root, 0, sizey);
	}
};

/*
 *	TEST MATRIX
 */
#include <cstdio>

vector< vector<int> > A;

int query(int lx, int rx, int ly, int ry) {
	int ans = 0;
	for(int i=lx; i<=rx; i++) {
		for(int j=ly; j<=ry; j++) {
			ans += A[i][j];
		}
	}
	return ans;
}

void update(int x, int y, int v) {
	A[x][y] += v;
}

bool test() {
	int N = 500, nTests = 100000;
	int lx, rx, ly, ry, x, y, v;
	A.resize(N);
	for(int i=0; i<N; i++) {
		A[i].assign(N, 0);
	}
	SegmentTree2D st(N, N);
	printf("starting tests...\n");
	for(int q=1; q<=nTests; q++) {
		x = rand()%N;
		y = rand()%N;
		v = rand()%N;
		st.update(x, y, v);
		update(x, y, v);
		lx = rand()%N;
		rx = rand()%N;
		ly = rand()%N;
		ry = rand()%N;
		int q1 = query(lx, rx, ly, ry);
		int q2 = st.query(lx, rx, ly, ry);
		if (q1 != q2) {
			printf("Failed test %d, q1 = %d, q2 = %d\n", q, q1, q2);
			return false;
		}
	}
	printf("all tests passed\n");
	return true;
}

int main() {
	test();
	return 0;
}
