#include <bits/stdc++.h>
using namespace std;
#define MAXN 500009
typedef long long int ll;

int vis[MAXN];
int dir[MAXN];
ll val[MAXN] ={};
int adjList[MAXN][2];
vector<int> toposort;

void ts(int u){
	vis[u] = true;
	if (u==0)return;
	
	for (int j=0,v;j<2;j++){
		v = adjList[u][j];
		if (!vis[v])ts(v);
	}
	toposort.push_back(u);
}

char aux[2] = {'L','R'};

int main(){
	int m,a,b;
	ll n;
	char c;
	
	scanf("%I64d%d",&n,&m);
	for (int i=1;i<=m;i++){
		scanf(" %c%d%d",&c,&a,&b);
		dir[i] = c=='L'?0:1;
		adjList[i][0] = a;
		adjList[i][1] = b;
	}
	memset(vis,0,sizeof(vis));
	ts(1);
	val[1] = n;
	reverse(toposort.begin(),toposort.end());
	for (int i=0;i<(int)toposort.size();i++){
		int u = toposort[i];
		ll qtt = val[u];
		ll l[2];
		if (qtt%2==0)l[0] = qtt/2, l[1] = qtt/2;
		else l[0] = qtt/2 + 1, l[1] = qtt/2;
		if (dir[u]==1)swap(l[0],l[1]);
		
		for (int i=0;i<2;i++)val[adjList[u][i]]+=l[i];
	}
	for (int i=1;i<=m;i++)printf("%c",aux[(val[i]+dir[i])%2]);
	printf("\n");
}