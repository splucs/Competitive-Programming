#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#define MAXM 100009
#define MAXN 100009
using namespace std;

typedef pair<int, int> ii;

struct node{
	int par, parw, gson;
	int chain;
	int h, size;
	vector<ii> adj;
} nodes[MAXN];

int root, N;

class Chain{
private:
	vector<int> chnodes, parw;
	map<int, int> pos;
public:
	int size, h;
	Chain(){}
	int upnode(){ return nodes[chnodes[0]].par; }
	int upchain(){ return nodes[upnode()].chain; }
	int dist(int n) { return parw[pos[n]]; }
	void insert(int n){
		pos[n] = (int)chnodes.size();
		chnodes.push_back(n);
	}
	void close(){
		size = (int)chnodes.size();
		h = nodes[chnodes[0]].h;
		parw.clear();
		for(int i=0, n; i<size; i++){
			n = chnodes[i];
			parw.push_back(nodes[n].parw + (i>0 ? parw.back() : 0));
		}
	}
};

vector<Chain> chains;

int LCA(int na, int nb){
	int ca = nodes[na].chain, cb = nodes[nb].chain;
	while(ca!=cb){
		if (chains[ca].h>chains[cb].h){
			na = chains[ca].upnode();
			ca = chains[ca].upchain();
		}
		else {
			nb = chains[cb].upnode();
			cb = chains[cb].upchain();
		}
	}
	if (nodes[na].h > nodes[nb].h) return nb;
	else return na;
}

int dist(int na, int nb){
	int ca = nodes[na].chain, cb = nodes[nb].chain;
	int ans = 0;
	while(ca!=cb){
		if (chains[ca].h>chains[cb].h){
			ans += chains[ca].dist(na);
			na = chains[ca].upnode();
			ca = chains[ca].upchain();
		}
		else {
			ans += chains[cb].dist(nb);
			nb = chains[cb].upnode();
			cb = chains[cb].upchain();
		}
	}
	if (nodes[na].h > nodes[nb].h)
		ans += chains[ca].dist(na) - chains[cb].dist(nb);
	else ans += chains[cb].dist(nb) - chains[ca].dist(na);
	return ans;
}

int dfs(int u){
	nodes[u].size = 1;
	nodes[u].h = 1 + nodes[nodes[u].par].h;
	int v, maxsize = 0;
	for(int i = 0; i<(int)nodes[u].adj.size(); i++){
		ii & p = nodes[u].adj[i]; v = p.first;
		if (v == nodes[u].par){
			nodes[u].parw = p.second;
			continue;
		}
		nodes[v].par = u;
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
	for(int i=0, v, w; i<(int)nodes[u].adj.size(); i++){
		v = nodes[u].adj[i].first;
		if (v == nodes[u].par)
			continue;
		if (nodes[u].gson == v)
			buildchains(v, cur);
		else{
			chains.push_back(Chain());
			buildchains(v, (int)chains.size()-1);
		}
	}
}

void build(){
	nodes[root].h=1;
	nodes[root].par=-1;
	dfs(root);
	chains.clear();
	chains.push_back(Chain());
	buildchains(root, 0);
}

int main(){
	scanf("%d", &N);
	int a, b, c;
	for(int i=0; i<N-1; i++){
		scanf("%d %d %d", &a, &b, &c);
		nodes[a].adj.push_back(ii(b, c));
		nodes[b].adj.push_back(ii(a, c));
	}
	root = 1;
	build();
	while(scanf("%d %d", &a, &b)!=EOF){
		printf("LCA(%d, %d) = %d, ", a, b, LCA(a,b));
		printf("dist(%d, %d) = %d\n", a, b, dist(a,b));
	}
	return 0;
}