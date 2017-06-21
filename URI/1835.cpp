#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

int main()
{
	int T, N, M, x, y, res;
	vector<vector<int> >adj;
	queue<int> fila;
	bool visited[109];
	scanf("%d", &T);
	for(int caso=1; caso<=T; caso++){
		scanf("%d %d", &N, &M);
		adj.resize(N+1);
		for(int i=0; i<M; i++){
			scanf("%d %d", &x, &y);
			adj[x].push_back(y);
			adj[y].push_back(x);
		}
		for(int i=1; i<=N; i++) visited[i]=false;
		res=-1;
		for(int i=1; i<=N; i++){
			if(visited[i]) continue;
			res++;
			fila.push(i);
			visited[i]=true;
			while(!fila.empty()){
				x = fila.front();
				fila.pop();
				for(int j=0; j<(int) adj[x].size(); j++){
					if(!visited[adj[x][j]]){
						visited[adj[x][j]] = true;
						fila.push(adj[x][j]);
					}
				}
			}
		}
		if(res==0) printf("Caso #%d: a promessa foi cumprida\n", caso);
		else printf("Caso #%d: ainda falta(m) %d estrada(s)\n", caso, res);
		for(int i=1; i<=N; i++) adj[i].clear();
	}
	return 0;
}