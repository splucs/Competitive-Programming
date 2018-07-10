#include <cstdio>
#include <cmath>
#define MAXN 100009
#define MAXLOGN 20

/*
 * Sparse Table
 */

int comp(int a, int b) {
	return min(a,b);
}

class SparseTable{
private:
	int st[MAXN][MAXLOGN];
	int sz;
public:
	SparseTable(int* st, int* en) {
		sz = int(en - st);
		for(int i=0; i<sz; i++) st[i][0] = st[i];
		for(int j = 1; 1 << j <= sz; j++)
			for(int i=0; i + (1<<j) <= sz; i++)
				st[i][j] = comp(st[i][j-1], st[i+(1<<(j-1))][j-1]);
	}
	int query(int l, int r) {
		int k = (int)floor(log((double)r-l+1) / log(2.0)); // 2^k <= (j-i+1)
		return comp(st[l][k], st[r-(1<<k)+1][k]);
	}
};