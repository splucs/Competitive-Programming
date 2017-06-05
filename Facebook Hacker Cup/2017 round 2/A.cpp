#include <cstdio>
#include <algorithm>
using namespace std;
#define INF (1LL<<60)
#define MAXN 609

typedef long long ll;
int T, N, M;
ll C[MAXN][MAXN], dp[MAXN][MAXN];

void CalculateDp(int i, int min_j, int max_j, int min_k, int max_k)
{
	if (min_j > max_j) return;
	int j = (min_j + max_j)/2;
	int best_k = -1;
	ll ans = INF, cur;
	for(int k = min_k; k <= max_k; k++)
	{
		cur = dp[i+1][j+k] + C[i][k] + (k*1LL*k);
		if (cur < ans)
		{
			ans = cur;
			best_k = k;
		}
	}
	dp[i][j] = ans;
	CalculateDp(i, min_j, j-1, best_k, max_k);
	CalculateDp(i, j+1, max_j, min_k, best_k);
}

int main()
{
	scanf("%d", &T);
	for(int caseNo = 1; caseNo <= T; caseNo++)
	{
		scanf("%d %d", &N, &M);
		for(int i=1; i<=N; i++)
		{
			for(int j=1; j<=M; j++){
				scanf("%lld", &C[i][j]);
			}
			sort(C[i]+1, C[i]+M+1);
			C[i][0] = 0;
			for(int j=1; j<=M; j++){
				C[i][j] += C[i][j-1];
			}
		}

		for(int i=N+1; i>=1; i--)
		{
			for(int j=0; j<i-1; j++)
			{
				dp[i][j] = INF;
			}
			for(int j=N; j<MAXN; j++)
			{
				dp[i][j] = 0;
			}
			CalculateDp(i, i-1, N-1, 0, M);
		}
		printf("Case #%d: %lld\n", caseNo, dp[1][0]);
	}
	return 0;
}