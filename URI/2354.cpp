#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;
#define MAXN 203
#define INF 100000000
#define VARPOS 54
#define LASTPOS 120

vector<int> adjList[MAXN];
int p[MAXN],cap[MAXN][MAXN]={}, dist[MAXN];

int augment(int v,int minEdge,int s){
	if (v==s)return minEdge;
	else if (p[v]!=-1){
		int f = augment(p[v],min(minEdge,cap[p[v]][v]),s);
		cap[p[v]][v]-=f;
		cap[v][p[v]]+=f;
		return f;
	}
	return 0;
}

bool bfs(int s,int t){
	int u,v;
	memset(&dist,-1,sizeof dist);
	dist[s]=0;
	queue<int> q;q.push(s);
	memset(&p,-1,sizeof p);
	while(!q.empty()){
		u = q.front();q.pop();
		if (u==t) break;
		for (int i=0;i<(int)adjList[u].size();i++){
			v = adjList[u][i];
			if (dist[v]<0&&cap[u][v]>0){
				dist[v]=dist[u]+1;
				q.push(v);
				p[v]=u;
			}
		}
	}
	return dist[t]>=0;
}

int edmondsKarp(int s,int t){
	int result = 0;
	while(bfs(s,t)){
		result+=augment(t,INF,s);
	}
	return result;
}

int main(){
	
	int n,a,b;
	scanf("%d",&n);
	for (int i=1;i<=n;i++){
		scanf("%d%d",&a,&b);
		adjList[i].push_back(a+	VARPOS);
		adjList[i].push_back(b+VARPOS);
		adjList[0].push_back(i);
		adjList[i+VARPOS].push_back(LASTPOS);
		adjList[a+	VARPOS].push_back(i);
		adjList[b+VARPOS].push_back(i);
		adjList[i].push_back(0);
		adjList[LASTPOS].push_back(i+VARPOS);
	}
	int wolf = 0,cnt=0,wolf1,wolf2;
	for (int i=1;i<=n;i++){
		wolf=0;
		wolf1 = adjList[i][0]-VARPOS;
		wolf2 = adjList[i][1]-VARPOS;
		
		memset(&cap,0,sizeof cap);
		
		for (int j=1;j<=n;j++){
			
			a = adjList[j][0];
			b = adjList[j][1];
			if (j==i){
				cap[j][a]=0;
				cap[j][b]=0;
				cap[0][j]=0;
			}
			else if (a-VARPOS==i||b-VARPOS==i){
				wolf++;
				cap[j][a]=cap[j][b] = 0;
				cap[0][j]=0;
			}else{
				cap[j][b]=cap[j][a]=1;
				cap[0][j]=1;
			}
		}for (int j=1;j<=n;j++){
			if (j!=wolf1&&j!=wolf2)cap[j+VARPOS][LASTPOS]=max(0,wolf-1);
			else cap[j+VARPOS][LASTPOS]=max(0,wolf-2);
		}//printf("\n");
		a = edmondsKarp(0,LASTPOS);
		//printf("%d %d\n",wolf,a);
		if (wolf==0||a+wolf!=n-1)cnt++;
	}printf("%d\n",cnt);
}
