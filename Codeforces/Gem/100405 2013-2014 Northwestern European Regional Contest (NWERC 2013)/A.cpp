#include <bits/stdc++.h>
using namespace std;
#define MAXN 2009
#define INF 1000000009
typedef pair<int,int> ii;
typedef pair<int,ii> iii;

vector<iii> vals;
vector<ii> ans;
int cost[MAXN][MAXN];

int main() {
	int N,a,u,v,b,c;
	bool first = false;
	
	while(scanf("%d", &N) != EOF) {
		vals.clear();
		ans.clear();
		
		if (first)printf("\n");
		first = true;
		
		for (int i=0;i<N;i++){
			for (int j=0;j<N;j++){
				scanf("%d",&a);
				if (j>i)vals.push_back(iii(a,ii(i,j)));
				cost[i][j] = INF;
			}
		}
		sort(vals.begin(),vals.end());
		for (int i=0;i<vals.size() && ans.size()!=N;i++){
			c = vals[i].first;
			u = vals[i].second.first;
			v = vals[i].second.second;
			
			for (int j=0;j<ans.size();j++){
				a = ans[j].first;
				b = ans[j].second;
				cost[u][v] = cost[v][u] = min(cost[u][v],cost[u][a]+cost[a][v]);
				cost[u][v] = cost[v][u] = min(cost[u][v],cost[u][b]+cost[b][v]);
			}
			
			if (cost[u][v] == c) {
				continue;
			}
			cost[u][v] = cost[v][u] = c;
			ans.push_back(ii(u,v));
		}int k =0;
		while (ans.size()<N)ans.push_back(ans[0]);
		for (int i=0;i<(int)ans.size();i++){
			a = ans[i].first;
			b = ans[i].second;
			printf("%d %d %d\n",a+1,b+1,cost[a][b]);
		}
	}	
}