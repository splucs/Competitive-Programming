#include <cstdio>
#include <cstring>
#define MAXN 79

int n, pair[MAXN], head, tail, queue[MAXN], start, finish, newBase, parent[MAXN], base[MAXN];
bool adjMat[MAXN][MAXN], inQueue[MAXN], inPath[MAXN], inBlossom[MAXN];

void push(int u) {
    queue[tail++] = u; 
    inQueue[u] = true;
}

int findCommonAncestor(int u, int v) {
    memset(inPath, 0, sizeof(inPath));
    while(true) {
        u = base[u];
        inPath[u] = true;
        if (u == start)break;
        u = parent[pair[u]];
    }
    while(true) {
        v = base[v];
        if (inPath[v]) break;
        v = parent[pair[v]];
    }
    return v;
}

void resetTrace(int u) {
    int v;
    while (base[u] != newBase) {
        v = pair[u];
        inBlossom[base[u]] = 1;
        inBlossom[base[v]] = 1;
        u = parent[v];
        if (base[u] != newBase) parent[u] = v;
    }
}

void blossomContract(int u,int v) {
    newBase = findCommonAncestor(u, v);
    memset(inBlossom, 0, sizeof(inBlossom));
    resetTrace(u);
    resetTrace(v);
    if (base[u] != newBase) parent[u]= v;
    if (base[v] != newBase) parent[v]= u;
    for(u=1;u<=n;u++)
        if (inBlossom[base[u]]) {
            base[u]= newBase;
            if (!inQueue[u]) push(u);
        }
}

void findAugmentingPath() {
    int u, v;
    memset(inQueue, false, sizeof(inQueue));
    memset(parent, 0, sizeof(parent));
    for(u = 1; u <= n; u++) base[u]=u; 
    head = 1; tail = 1;
    push(start);
    finish = 0;
    while (head < tail) {
        u = queue[head++];
        for (v = 1; v <= n; v++)
            if (adjMat[u][v] && base[u]!=base[v] && pair[u]!= v)
                if (v == start ||( pair[v] > 0 && parent[pair[v]] > 0))
                    blossomContract(u, v);
                else if (parent[v] == 0) {
                    parent[v] = u;
                    if (pair[v] > 0)  push(pair[v]);
                    else { finish = v; return; }
                }
    }
}

void augmentPath() {
    int u,v,w;
    u = finish;
    while(u > 0) {
        v = parent[u]; w = pair[v];
        pair[v] = u; pair[u] = v; u = w;
    }
}

void edmondskarpmaxmatch() {
    int u;
    memset(pair,0,sizeof(pair));
    for(u = 1; u <= n; u++)
        if (pair[u] == 0)
        {
            start = u;
            findAugmentingPath();
            if (finish > 0) augmentPath();
        }
}

int main(){

    return 0;
}
