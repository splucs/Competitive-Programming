#include <algorithm>
#include <vector>
using namespace std;
#define INF (1<<30)

const int neutral = 0;
int comp(int a, int b) {
	return a+b;
}

class SegmentTree2D {
	int sizex, sizey, ix, jx, iy, jy, x, y, v;
	vector< vector<int> > st;
#define parent(p) (p >> 1)
#define left(p) (p << 1)
#define right(p) ((p << 1) + 1)
	void buildx(int px, int lx, int rx, vector< vector<int> > & A) {
		if(lx != rx) {
			int mx = (lx + rx) / 2;
			buildx(left(px), lx, mx, A);
			buildx(right(px), mx+1, rx, A);
		}
		buildy(px, lx, rx, 1, 0, sizey-1, A);
	}
	void buildy(int px, int lx, int rx, int py, int ly, int ry, vector< vector<int> > & A) {
		if(ly == ry) {
			if(lx == rx) st[px][py] = A[lx][ly];
			else st[px][py] = comp(st[left(px)][py], st[right(px)][py]);
		}
		else {
			int my = (ly + ry) / 2;
			buildy(px, lx, rx, left(py), ly, my, A);
			buildy(px, lx, rx, right(py), my+1, ry, A);
			st[px][py] = comp(st[px][left(py)], st[px][right(py)]);
		}
	}
	int queryx(int px, int lx, int rx) {
		if(lx > jx || rx < ix) return neutral;
		if(lx >= ix && rx <= jx) return queryy(px, 1, 0, sizey-1);
		int mx = (lx + rx) / 2;
		int p1x = queryx(left(px), lx, mx);
		int p2x = queryx(right(px), mx+1, rx);
		return comp(p1x, p2x);
	}
	int queryy(int px, int py, int ly, int ry) {
		if(ly > jy || ry < iy) return neutral;
		if(ly >= iy && ry <= jy) return st[px][py];
		int my = (ly + ry) / 2;
		int p1y = queryy(px, left(py), ly, my);
		int p2y = queryy(px, right(py), my+1, ry);
		return comp(p1y, p2y);
	}
	void updatex(int px, int lx, int rx) {
		if(lx > x || rx < x) return;
		if(lx < rx) {
			int mx = (lx + rx) / 2;
			updatex(left(px), lx, mx);
			updatex(right(px), mx+1, rx);
		}
		updatey(px, lx, rx, 1, 0, sizey-1);
	}
	void updatey(int px, int lx, int rx, int py, int ly, int ry) {
		if(ly > y || ry < y) return;
		if(ly == ry) {
			if(lx == rx) st[px][py] = v;
			else st[px][py] = comp(st[left(px)][py],st[right(px)][py]);
		}
		else {
			int my = (ly + ry) / 2;
			updatey(px, lx, rx, left(py),ly,my);
			updatey(px, lx, rx, right(py), my+1,ry);
			st[px][py] = comp(st[px][left(py)], st[px][right(py)]);
		}
	}
public:
	SegmentTree2D(vector< vector<int> > & A) {
		sizex = A.size();
		sizey = A[0].size();
		st.assign(4*sizex+9, vector<int>(4*sizey+9));
		buildx(1, 0, sizex-1, A);
	}
	void update(int _x, int _y, int _v) {
		x = _x; y = _y; v = _v;
		updatex(1, 0, sizex - 1);
	}
	int query(int lx, int rx, int ly, int ry) {
		ix = lx; jx = rx; iy = ly; jy = ry;
		return queryx(1, 0, sizex - 1);
	}
};

/*
 *	TEST MATRIX
 */
#include <cstdio>

vector< vector<int> > A;

int query(int lx, int rx, int ly, int ry) {
	int ans = neutral;
	for(int i=lx; i<=rx; i++){
		for(int j=ly; j<=ry; j++){
			ans = comp(ans, A[i][j]);
		}
	}
	return ans;
}

void update(int x, int y, int v) {
	A[x][y] = v;
}

bool test(){
	int N = 500, nTests = 100000;
	int lx, rx, ly, ry, x, y, v;
	A.resize(N);
	for(int i=0; i<N; i++){
		A[i].resize(N);
		for(int j=0; j<N; j++){
			A[i][j] = rand() % N;
		}
	}
	SegmentTree2D st(A);
	printf("starting tests...\n");
	for(int q=1; q<=nTests; q++){
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
		if (q1 != q2){
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
