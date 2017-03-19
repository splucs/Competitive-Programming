#include <bits/stdc++.h>
using namespace std;
#define MAXN 29
#define UNVIS -1
#define INF (1<<30)

int num[MAXN], N, M, low[MAXN], parent[MAXN], counter, root, rootChildren, a[MAXN], b[MAXN], w[MAXN];
bool bridge;
vector<int> adj[MAXN];

void tarjan(int u)
{
	low[u] = num[u] = counter++;
	for(int j=0, v; j<(int)adj[u].size(); j++){
		v = adj[u][j];
		if (num[v] == UNVIS){
			parent[v] = u;
			if (u == root) rootChildren++;
			tarjan(v);
			if (low[v] > num[u]) bridge = true;
			low[u] = min(low[u], low[v]);
		}
		else if (v != parent[u])
			low[u] = min(low[u], num[v]);
	}
}

int main()
{
	int T = 1;
	while(scanf("%d %d", &N, &M), (N||M))
	{
		for(int i=0; i<M; i++)
		{
			scanf("%d %d %d", a+i, b+i, w+i);
		}
		int cur, ans = INF;
		for(int mask=0; mask<(1<<M); mask++)
		{
			cur = 0;
			for(int i=1; i<=N; i++){
				adj[i].clear();
			}
			for(int i=0; i<M; i++){
				if ((mask & (1<<i))>0){
					adj[a[i]].push_back(b[i]);
					adj[b[i]].push_back(a[i]);
					cur += w[i];
				}
			}
			counter = 0;
			bridge = false;
			memset(&num, UNVIS, sizeof num);
			memset(&low, 0, sizeof low);
			memset(&parent, 0, sizeof parent);
			bool con = false;
			for(int i=1; i<=N; i++){
				if (num[i]==UNVIS){
					if (con){
						bridge = true;
						break;
					}
					root = i;
					rootChildren = 0;
					tarjan(i);
					con = true;
				}
			}
			if (!bridge) ans = min(ans, cur);
		}
		if (ans == INF) printf("There is no reliable net possible for test case %d.\n", T++);
		else printf("The minimal cost for test case %d is %d.\n", T++, ans);		
	}
}