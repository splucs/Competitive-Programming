#include <cstdio>
#include <cstring>
#define min(a,b) (a>b?b:a);

int dp[8][256], mat[8][8], t, n;
bool calculated[8][256];

int DP(int row, int mask){
	if (row==n) return 0;
	if (calculated[row][mask]) return dp[row][mask];
	int ans = (1<<30);
	for(int i=0; i<n; i++){
		if ((mask & (1<<i)) > 0) continue;
		ans = min(ans, mat[row][i] + DP(row+1, mask | (1<<i)));
	}
	calculated[row][mask]=true;
	return dp[row][mask] = ans;
}

int main()
{
	scanf("%d", &t);
	while(t-->0){
		scanf("%d", &n);
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				scanf("%d", &mat[i][j]);
			}
		}
		memset(&calculated, false, sizeof calculated);
		printf("%d\n", DP(0, 0));
	}
	return 0;
}