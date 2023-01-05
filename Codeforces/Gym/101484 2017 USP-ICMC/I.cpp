#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009

typedef long long ll;
int N;
ll a[MAXN][MAXN], m[MAXN][MAXN], row[MAXN], mrow[MAXN], col[MAXN], mcol[MAXN], sum, msum;

bool solve() {
	if (N == 1) return true;
	
	memset(&row, 0, sizeof row);
	memset(&col, 0, sizeof col);
	sum = 0;
	
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			row[i] += a[i][j];
			col[j] += a[i][j];
			sum += a[i][j];
		}
	}
	
	if (sum%(2*N-1) != 0) return false;
	msum = sum/(2*N-1);
	
	for(int i=0; i<N; i++) {
		if ((row[i] - msum) % (N-1) != 0) return false;
		mrow[i] = (row[i] - msum) / (N-1);
	}
	for(int j=0; j<N; j++) {
		if ((col[j] - msum) % (N-1) != 0) return false;
		mcol[j] = (col[j] - msum) / (N-1);
	}
	
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			m[i][j] = mrow[i] + mcol[j] - a[i][j];
			if (m[i][j] != 0 && m[i][j] != 1) return false;
		}
	}
	
	return true;
}

int main() {
	
	scanf("%d", &N);
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			scanf("%d", &a[i][j]);
		}
	}
	
	if (solve()) printf("1\n");
	else printf("0\n");
	
	return 0;
}