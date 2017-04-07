#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
using namespace std;
#define MAXN 20009

typedef pair<int, int> ii;

int N, M, S, A, B, P, u, w;

vector<int> taken;

struct edge{
    int from;
    int to;
    int weight;
    edge(int t, int f, int w){
        to = t;
        from = f;
        weight = w;
    }
};


bool operator < (edge a, edge b){
    return a.weight < b.weight;
}

vector< vector<edge> > AdjList;
vector< vector<edge> > TreeAdjList;
priority_queue<edge> pq;
vector<int> depth;
vector<ii> upedge;

void process(int vtx){
    taken[vtx] = 1;
    edge v(-1, -1, -1);
    for(int j=0; j<(int)AdjList[vtx].size(); j++){
        v = AdjList[vtx][j];
        if (!taken[v.to]) pq.push(v);
    }
}

void dfs(int vtx){
    edge v(-1, -1, -1);
    for(int j=0; j<(int)TreeAdjList[vtx].size(); j++){
        v = TreeAdjList[vtx][j];
        if (depth[v.to] < 0){
            depth[v.to] = depth[vtx] + 1;
            upedge[v.to] = ii(vtx, v.weight);
            dfs(v.to);
        }
    }
}

int LCA(int u, int v){
    int maxu = (1<<20);
    int maxv = (1<<20);
    while(depth[u] > depth[v]){
        maxu = min(maxu, upedge[u].second);
        u = upedge[u].first;
    }
    while(depth[u] < depth[v]){
        maxv = min(maxv, upedge[v].second);
        v = upedge[v].first;
    }
    while(u != v){
        maxu = min(maxu, upedge[u].second);
        u = upedge[u].first;
        maxv = min(maxv, upedge[v].second);
        v = upedge[v].first;
    }
    return min(maxu, maxv);
}

int main(){
    int root;
    while(scanf("%d %d %d", &N, &M, &S)!=EOF){

        AdjList.clear(); AdjList.resize(N);
        TreeAdjList.clear(); TreeAdjList.resize(N);

        for(int i=0; i<M; i++){
            scanf("%d %d %d", &A, &B, &P);
            AdjList[A-1].push_back(edge(B-1, A-1, P));
            AdjList[B-1].push_back(edge(A-1, B-1, P));
        }

        taken.clear(); taken.resize(N); taken.assign(N, 0);
        process(0);
        edge front(-1, -1, -1);
        while(!pq.empty()){
            front = pq.top(); pq.pop();
            if (!taken[front.to]){
                TreeAdjList[front.from].push_back(edge(front.to, front.from, front.weight));
                TreeAdjList[front.to].push_back(edge(front.from, front.to, front.weight));
                process(front.to);
            }
        }

        depth.clear(); depth.resize(N); depth.assign(N, -1);
        upedge.clear(); upedge.resize(N);
        root = N/2;
        depth[root] = 0; dfs(root);

        for(int i=0; i<S; i++){
            scanf("%d %d", &A, &B);
            printf("%d\n", LCA(A-1, B-1));
        }
    }

    return 0;
}
