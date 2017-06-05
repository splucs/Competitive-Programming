#include <cstdio>
#include <cstring>
#include <map>
#include <algorithm>
using namespace std;
#define MAXN 109
#define MAXM 5009
#define INF (1LL<<60)

typedef long long ll;
int T, N, M, K;
ll dist[MAXN][MAXN];
int S[MAXM], D[MAXM];
map<int, ll> dp[MAXM][3];

//0 -> need to go pick up k
//1 -> has k in truck
//2 -> has k and k+1 in truck

ll DP(int k, int b, int c)
{
	if (c < 1 || c > N) return INF;
	if (k > K) return 0;
	if (dp[k][b].count(c)) return dp[k][b][c];
	if (b == 0)
	{
		return dp[k][b][c] = min(INF,
			dist[c][S[k]] + DP(k, 1, S[k]));
	}
	if (b == 1)
	{
		return dp[k][b][c] = min(INF, min(
			dist[c][D[k]] + DP(k+1, 0, D[k]),
			dist[c][S[k+1]] + DP(k, 2, S[k+1])));
	}
	if (b == 2)
	{
		return dp[k][b][c] = min(INF,
			dist[c][D[k]] + DP(k+1, 1, D[k]));
	}
}

int main()
{
	int A, B;
	ll G;
	scanf("%d", &T);
	for(int caseNo = 1; caseNo <= T; caseNo++)
	{
		scanf("%d %d %d", &N, &M, &K);
		for(int i=0; i<MAXN; i++)
		{
			for(int j=0; j<MAXN; j++)
			{
				dist[i][j] = INF;
			}
		}
		for(int i=1; i<=M; i++)
		{
			scanf("%d %d %lld", &A, &B, &G);
			if (dist[A][B] > G)
			{
				dist[A][B] = dist[B][A] = G;
			}
		}
		for(int i=1; i<=N; i++)
		{
			dist[i][i] = 0;
		}
		for(int k=1; k<=N; k++)
		{
			for(int i=1; i<=N; i++)
			{
				for(int j=1; j<=N; j++)
				{
					if (dist[i][j] > dist[i][k] + dist[k][j])
					{
						dist[i][j] = dist[i][k] + dist[k][j];
					}
				}
			}
		}
		for(int k=1; k<=K; k++)
		{
			scanf("%d %d", &S[k], &D[k]);
			dp[k][0].clear();
			dp[k][1].clear();
			dp[k][2].clear();
		}
		S[K+1] = N+1;
		D[K+1] = N+2;
		ll ans = DP(1, 0, 1);
		if (ans >= INF) ans = -1;
		printf("Case #%d: %d\n", caseNo, ans);
	}
	return 0;
}