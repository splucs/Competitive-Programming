#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#define MAXN 100009
using namespace std;

struct node{
    int par, star, gson;
    int chain, original;
    int size, x;
    char qtype;
    vector<int> adj;
} nodes[MAXN];

int root, N;

class Chain{
private:
    vector<int> chnodes;
    map<int, int> pos;
public:
    int size;
    Chain() {}
    int upnode(){
        //printf("first of chain is %d, upnode is %d\n", chnodes[0]);
        return nodes[chnodes[0]].par;
    }
    int upchain() { return nodes[upnode()].chain; }
    bool count(int n) { return pos.count(n); }
    int next(int n) { return chnodes[pos[n] + 1]; }
    int first() { return chnodes[0]; }
    void insert(int n){
        pos[n] = (int)chnodes.size();
        chnodes.push_back(n);
    }
    void close(){
        size = (int)chnodes.size();
    }
    void printchain(){
        for(int i=0; i<size; i++){
            printf("%d ", chnodes[i]);
        }
        printf("\n");
    }
};

vector<Chain> chains;

int dfs(int u){
    nodes[u].size = 1;
    int v, maxsize = 0;
    for(int i=0; i<(int)nodes[u].adj.size(); i++){
        v = nodes[u].adj[i];
        if (v == nodes[u].par) continue;
        nodes[u].size += dfs(v);
        if (nodes[v].size > maxsize){
            nodes[u].gson = v;
            maxsize = nodes[v].size;
        }
    }
    return nodes[u].size;
}

void buildchains(int u, int cur){
    chains[cur].insert(u);
    nodes[u].chain = cur;
    if ((int)nodes[u].adj.size() <= 1)
        chains[cur].close();
    for(int i=0, v; i<(int)nodes[u].adj.size(); i++){
        v = nodes[u].adj[i];
        if (v == nodes[u].par) continue;
        if (nodes[u].gson == v) buildchains(v, cur);
        else{
            chains.push_back(Chain());
            buildchains(v, (int)chains.size() - 1);
        }
    }
}

void build(){
    nodes[root].par = root;
    dfs(root);
    //printf("dfs executed\n");
    chains.clear();
    chains.push_back(Chain());
    buildchains(root, 0);
    /*printf("chains built\n");
    for(int i=0; i<(int)chains.size(); i++){
        printf("chain %d, upnode = %d: ", i, chains[i].upnode());
        chains[i].printchain();
    }*/
}

int getPrev(int n, int s){
    int c = nodes[n].chain;
    if (chains[c].count(s)) return chains[c].next(s);
    else if (chains[c].upnode() == s) return chains[c].first();
    else return getPrev(chains[c].upnode(), s);
}


int main(){
    int Q, v, x; char qtype;
    root = 0;
    scanf("%d", &Q);
    for(int i=1; i<=Q; i++){
        scanf(" %c", &qtype);
        if (qtype == 'E'){
            scanf("%d %d", &v, &x);
            nodes[i].par = v;
            nodes[i].adj.push_back(v);
            nodes[v].adj.push_back(i);
            nodes[i].x = x;
            nodes[i].original = -1;
        }
        else{
            scanf("%d", &v);
            nodes[i].par = nodes[v].par;
            nodes[i].adj.push_back(nodes[v].par);
            nodes[nodes[v].par].adj.push_back(i);
            nodes[i].x = nodes[v].x;
            nodes[i].original = v;
        }
        nodes[i].qtype = qtype;
    }
   /* for(int i=1; i<=Q; i++){
        printf("par[%d] = %d\n", i, nodes[i].par);
    }*/
    build();
    for(int i=1; i<=Q; i++){
        if (nodes[i].qtype == 'E'){
            nodes[i].star = nodes[nodes[i].par].star;
        }
        else{
            nodes[i].star = getPrev(i, nodes[nodes[i].original].star);
            printf("%d\n",nodes[nodes[i].star].x);
        }
    }
    /*for(int i=1; i<=Q; i++){
        printf("s[%d] = %d, par[%d] = %d, x[%d] = %d\n", i, nodes[i].star, i, nodes[i].par, i, nodes[i].x);
    }*/
}