#include <bits/stdc++.h>
using namespace std;
#define MAXN 3009

typedef pair<int, pair<int, int> > iii;
#define triple(x,y,z) make_pair(x,make_pair(y,z))
map<iii, int> dp;
int a[3][MAXN], last[3][MAXN][MAXN];

int DP(const int x, const int y, const int z) {
	if (x < 0 || y < 0 || z < 0) return 0;
	if (dp.count(triple(x,y,z))) return dp[triple(x,y,z)];
	int ans = DP(x-1, y, z);
	int ny = last[1][y][a[0][x]];
	int nz = last[2][z][a[0][x]];
	if (x >=0 && ny >=0 && nz >= 0) ans = max(ans, 1+DP(x-1, ny-1, nz-1));
	return dp[triple(x,y,z)] = ans;
}

int main() {
	int T, N;
	scanf("%d", &T); 
	while(T-->0) {
		scanf("%d", &N);
		for(int k=0; k<3; k++) {
			for(int i=0; i<N; i++) {
				scanf("%d", &a[k][i]);
			}
		}
		for(int k=0; k<3; k++) {
			for(int i=0; i<N; i++) {
				for(int j=1; j<=N; j++) {
					if (i == 0) last[k][i][j] = -1;
					else last[k][i][j] = last[k][i-1][j];
				}
				last[k][i][a[k][i]] = i;
			}
		}
		dp.clear();
		printf("%d\n", DP(N-1, N-1, N-1));
	}
}