#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009
#define INF (1<<30)

int dp[MAXN][MAXN][2], vet[MAXN];

int DP(int i, int j, int b)
{
	if (dp[i][j][b] < INF) return dp[i][j][b];
	if (i>j) return dp[i][j][b] = 0;
	if (b == 0){
		if (vet[i] >= vet[j]) return dp[i][j][b] = DP(i+1, j, 1-b) - vet[i];
		else return dp[i][j][b] = DP(i, j-1, 1-b) - vet[j];
	}
	else{
		return dp[i][j][b] = max(DP(i+1, j, 1-b)+vet[i], DP(i, j-1, 1-b)+vet[j]);
	}
}

int main()
{
	int N, count=1;
	while(scanf("%d", &N), N)
	{
		for(int i=0; i<N; i++)
			for(int j=0; j<N; j++)
				dp[i][j][0] = dp[i][j][1] = INF;
		for(int i=0; i<N; i++)
		{
			scanf("%d", &vet[i]);
		}
		printf("In game %d, the greedy strategy might lose by as many as %d points.\n", count++, DP(0, N-1, 1));
	}
	return 0;
}