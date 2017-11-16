#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define MAXM 200009
typedef long long int ll;

struct edge{
	int v,num;
	ll cost;
	edge(){}
	edge(int v,int num,ll cost){
		this->v = v;
		this->cost = cost;
		this->num = num;
	}
	
	bool operator<(edge other)const{
		return cost>other.cost;
	}
};

int N,M;
vector<edge> adjList[MAXN];
vector<int> ans;
bool used[MAXM];

void djkstra(){
	priority_queue<edge> inuse;
	ll val[MAXN],cost,cost1;
	int u,v,num;
	
	memset(val,-1,sizeof(val));
	val[1] = 0;
	inuse.push(edge(1,0,0));
	edge e;
	
	while (!inuse.empty()){
		e = inuse.top();
		inuse.pop();
		
		u = e.v, cost = e.cost, num = e.num;
		
		if (cost>val[u])continue;
		
		ans.push_back(num);
		used[num] = true;
		
		for (int i=0;i<(int)adjList[u].size();i++){
			v = adjList[u][i].v;
			cost1 = cost + adjList[u][i].cost;
			
			if (val[v]<0||cost1<val[v]){
				val[v] = cost1;
				inuse.push(edge(v,adjList[u][i].num,cost1));
			}
		}
	}
	
}

int main(){
	int t,x,y;
	ll cost;
	
	freopen("algoritm.in","r",stdin);
	freopen("algoritm.out","w",stdout);
	
	scanf("%d",&t);
	while (t-->0){
		cin>>N>>M;
		ans.clear();
		for (int i=1;i<=N;i++)adjList[i].clear();
		for (int i=1;i<=M;i++){
			//x = i%N, y = (i+1)%N, cost = i+1;
			scanf("%d%d%I64d",&x,&y,&cost);
			adjList[x].push_back(edge(y,i,cost));
			used[i] = false;
		}
		djkstra();
		for (int i=1;i<=M;i++)if (!used[i])ans.push_back(i);
		
		for (int i=1;i<ans.size();i++){
			printf("%d ",ans[i]);
		}
		printf("\n");
	}
	
	
	fclose(stdin);
	fclose(stdout);
}