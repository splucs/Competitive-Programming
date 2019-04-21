#include <vector>
using namespace std;
#define MAXN 100009

#include <cstdio>

/*
 * Pre-Suf Table
 * Friend of the Sparse Table
 */

const int neutral = 0;
#define comp(a, b) ((a)+(b))

int top[2*MAXN];

class PresufTable {
	vector< vector<int> > f;
public:
	PresufTable(int* st, int* en) {
		int bit = 0, sz = int(en - st), n, k;
		for(n = 1, k = 0; n < sz; n <<= 1, k++);
		f.assign(k, vector<int>(n));
		for(int i = 0; i < n; i++) {
			while((1<<bit) <= i) bit++;
			top[i] = bit;
		}
		for(int i = 0; i < n; i++)
			f[0][i] = i < sz ? st[i] : neutral;
		for(int j = 0, len = 1; j <= k; j++, len <<= 1)
			for(int s = len; s < n; s += (len<<1)) {
				f[j][s] = st[s]; f[j][s-1] = st[s-1];
				for(int i = 1; i < len; i++) {
					f[j][s+i] = comp(f[j][s+i-1], st[s+i]);
					f[j][s-1-i] = comp(f[j][s-i], st[s-1-i]);
				}
			}
	}
	int query(int l, int r) {
		if (l == r) return f[0][r];
		int i = top[l^r] - 1;
		return comp(f[i][r], f[i][l]);
	}
};

/*
 * TEST MATRIX
 */

#include <cstdlib>
#define RANGE 10000

int arr[MAXN];

int query(int l, int r) {
	int ans = 0;
	for(int i = l; i <= r; i++) {
		ans += arr[i];
	}
	return ans;
}

bool test(int n, int ntests) {
	for(int i = 0; i < n; i++) arr[i] = /*rand()%RANGE*/ i;
	PresufTable pst(arr, arr+n);
	for(int test = 1; test <= ntests; test++) {
		int l = rand()%n;
		int r = rand()%n;
		if (l > r) swap(l, r);
		if (query(l, r) != pst.query(l, r)) {
			printf("failed test %d\n", test);
			return false;
		}
	}
	printf("all tests passed\n");
	return true;
}

int main() {
	test(10000, 10000);
}