#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
#define MAXN 109
#define MAXM 10009

vii adjList[MAXN];
vi Q,A[MAXM];
ii edges[MAXM];
vector<bool> T,Fcolors;
set<int> F;
set<int>::iterator it;
int c[MAXM], N, M, C;

class UnionFind {
private:
	vector<int> parent, rank;
public:
	UnionFind(int N) {
		rank.assign(N+1, 0);
		parent.assign(N+1, 0);
		for (int i = 0; i <= N; i++) parent[i] = i;
	}
	int find(int i) {
		while(i != parent[i]) i = parent[i];
		return i;
	}
	bool isSameSet(int i, int j) {
		return find(i) == find(j);
	}
	void unionSet (int i, int j) {
		if (isSameSet(i, j)) return;
		int x = find(i), y = find(j);
		if (rank[x] > rank[y]) parent[y] = x;
		else {
			parent[x] = y;
			if (rank[x] == rank[y]) rank[y]++;
		}
	}
};

vector<int> findCycle(int u,int v){
    vector<int> ans;
    vector<ii> prev;
    queue<int> inuse;

    prev.assign(N,ii(-1,-1));
    inuse.push(u);
    prev[u] = ii(u,-1);

    int w,nxt;

    while (!inuse.empty()){
        w = inuse.front();
        inuse.pop();

        if (w==v)break;

        for (int i=0;i<(int)adjList[w].size();i++){
            nxt = adjList[w][i].first;
            if (prev[nxt].first==-1){
                prev[nxt] = ii(w,adjList[w][i].second);
                inuse.push(nxt);
            }
        }
    }
    while (v!=u){
        ans.push_back(prev[v].second);
        v = prev[v].first;
    }
    return ans;
}

void start(){
    T.assign(M,false);Q.clear();
    for (int i=0;i<N;i++)adjList[i].clear();
    for (int i=0;i<M;i++)A[i].clear();
}

void greedyAugmentation(UnionFind &UF){
    int e,u,v;

    Fcolors.assign(C,false);

    for (it=F.begin();it!=F.end();it++){
        e = *it;
        u = edges[e].first, v = edges[e].second;
        UF.unionSet(u,v);
        adjList[u].push_back(ii(v,e));
        adjList[v].push_back(ii(u,e));
        Fcolors[c[e]] = true;
    }
    for (int i=0;i<M;i++){
        u = edges[i].first, v = edges[i].second;
        if (!UF.isSameSet(u,v)&&!Fcolors[c[i]]){
            UF.unionSet(u,v);
            adjList[u].push_back(ii(v,i));
            adjList[v].push_back(ii(u,i));
            Fcolors[c[i]] = true;
            F.insert(i);
        }
    }
    //printF();
}

void digraphConstruction(UnionFind &UF){
    int e;
    vector<int> cycle;

    for (int i=0;i<M;i++){
        if (F.count(i))continue;

        if (!Fcolors[c[i]])Q.push_back(i);
        else{
            for (it = F.begin();it!=F.end();it++){
                e = *it;
                if (c[e]==c[i]){
                    A[e].push_back(i);
                }
            }
        }

        if (!UF.isSameSet(edges[i].first,edges[i].second))T[i] = true;
        else{
            cycle = findCycle(edges[i].first,edges[i].second);
            for (int j=0;j<(int)cycle.size();j++)A[i].push_back(cycle[j]);
        }
    }
    //printA();
    //printQ();
    //printT();
}

bool augmentation(){
    queue<int> inuse;
    vector<int> prev;

    prev.assign(M,-1);
    for (int i=0;i<Q.size();i++){
        inuse.push(Q[i]);
        prev[Q[i]] = Q[i];
    }
    int u,v,found = -1;

    while (!inuse.empty()){
        u = inuse.front();
        inuse.pop();

        if (T[u]){
            found = u;
            break;
        }

        for (int i=0;i<(int)A[u].size();i++){
            v = A[u][i];
            if (prev[v]==-1){
                prev[v] = u;
                inuse.push(v);
            }
        }
    }
    if (found==-1)return false;
    u = found;
    while (true){
        if (F.count(u))F.erase(u);
        else F.insert(u);
        if (u==prev[u])break;
        u = prev[u];
    }
    return true;
}

void buildSpanningTree(){
    F.clear();

    while (true){
        UnionFind UF(M);
        start();
        greedyAugmentation(UF);
        digraphConstruction(UF);
        if (!augmentation())break;
    }
}

//URI 2128
int main(){
    int u,v,c1,t=1;
    while (scanf("%d%d%d",&N,&M,&C)!=EOF){
        for (int i=0;i<M;i++){
            scanf("%d%d%d",&u,&v,&c1);
            u--, v--, c1--;
            edges[i] = ii(u, v);
            c[i] = c1;
        }
        buildSpanningTree();
        if (F.size()!=N-1){
            printf("Instancia %d\nnao\n\n",t++);
        }else{
            printf("Instancia %d\nsim\n\n",t++);
        }
    }
}
