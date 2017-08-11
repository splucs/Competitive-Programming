#include <bits/stdc++.h>
using namespace std;
#define MAXN 20

typedef long long ll;
ll dp[MAXN][MAXN][MAXN], h[MAXN][MAXN][MAXN];

int main() {
	freopen("commandos.in", "r", stdin);
	
	int T, N;
	scanf("%d", &T);
	while(T-->0) {
		for(int i=0; i<MAXN; i++) {
			for(int j=0; j<MAXN; j++) {
				for(int k=0; k<MAXN; k++) {
					h[i][j][k] = 0;
				}
			}
		}
		scanf("%d", &N);
		int x, y, f, hos;
		while(N-->0) {
			scanf("%d %d %d %d", &f, &y, &x, &hos);
			h[x][y][f] += hos;
		}
		for(f=1; f<=10; f++) {
			for(x=10; x>0; x--) {
				for(y=10; y>0; y--) {
					dp[x][y][f] = 0;
					if (f > 1) dp[x][y][f] = max(dp[x][y][f], dp[x][y][f-1]);
					if (y < 10) dp[x][y][f] = max(dp[x][y][f], dp[x][y+1][f]);
					if (x < 10) dp[x][y][f] = max(dp[x][y][f], dp[x+1][y][f]);
					dp[x][y][f] += h[x][y][f];
				}
			}
		}
		printf("%I64d\n", dp[1][1][10]);
	}
	
	fclose(stdin); 
	return 0;
}