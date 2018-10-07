#include <vector>
#include <bitset>
#include <algorithm>
using namespace std;

/*
 * XOR-SAT or Gauss XOR Elimination O(n*(m^2)/64)
 */

#define MAXN 2009

vector<int> B;
vector< bitset<MAXN> > A;
bitset<MAXN> x;

bool check() {
	int n = A.size(), m = MAXN;
	for(int i = 0; i < n; i++) {
		int acum = 0;
		for(int j = 0; j < m; j++) {
			if (A[i][j]) acum ^= x[j];
		}
		if (acum != B[i]) return false;
	}
	return true;
}

bool gaussxor() {
	int cnt = 0, n = A.size(), m = MAXN;
	bitset<MAXN> vis; vis.set();
	for(int j = m-1, i; j >= 0; j--) {
		for(i = cnt; i < n; i++) {
			if (A[i][j]) break;
		}
		if (i == n) continue;
		swap(A[i], A[cnt]); swap(B[i], B[cnt]);
		i = cnt++; vis[j] = 0;
		for(int k = 0; k < n; k++) {
			if (i == k || !A[k][j]) continue;
			A[k] ^= A[i]; B[k] ^= B[i];
		}
	}
	x = vis;
	for(int i = 0; i < n; i++) {
		int acum = 0;
		for(int j = 0; j < m; j++) {
			if (!A[i][j]) continue;
			if (!vis[j]) {
				vis[j] = 1;
				x[j] = acum^B[i];
			}
			acum ^= x[j];
		}
		if (acum != B[i]) return false;
	}
	return true;
}

/*
 * Codeforces 101908M
 */

#include <cstdio>

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	for(int i = 0; i < n; i++) {
		char c, str[10];
		scanf(" %c", &c);
		int val = 1;
		bitset<MAXN> eq;
		while(scanf(" %s", str) != EOF && str[0] != 'a') {
			//printf("%s ", str);
			if (str[0] == 'n') val ^= 1;
			if (str[0] == 'x') {
				int k;
				sscanf(str+1, "%d", &k);
				eq[k-1] = 1^eq[k-1];
			}
		}
		//printf("\n");
		A.push_back(eq);
		B.push_back(val);
	}
	if (!gaussxor()) printf("impossible\n");
	else {
		for(int j = 0; j < m; j++) {
			printf("%c", x[j] ? 'T' : 'F');
		}
		printf("\n");
	}
	return 0;
}