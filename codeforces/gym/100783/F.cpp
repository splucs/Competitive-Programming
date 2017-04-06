#include <bits/stdc++.h>
using namespace std;
#define MAXN 50009


struct rec{
	int b, t, l, r;
	area(){
		return abs((r-l)*(t-b));
	}
};
rec vet[MAXN];
bool vis[MAXN];
vector<int> adjList[MAXN];

struct xcomp{
	bool operator()(int a, int b){
		return vet[a].l < vet[b].l;
	}
};
struct ycomp{
	bool operator()(int a, int b){
		return vet[a].b < vet[b].b;
	}
};

map<int, set<int, vector<int>, &xsort> > bot, top;
map<int, set<int, vector<int>, &ysort> > lef, rig;

bool areAdj(rec i, rec j){
	if (i.t == j.b || i.b == j.t){
		if ((i.r >= j.l && i.r <= j.r) || (i.l >= j.l && i.l <= j.r)) return true;
		if ((j.r >= i.l && j.r <= i.r) || (j.l >= i.l && j.l <= i.r)) return true;
	}
	if (i.l == j.r || i.r == j.l){
		if ((i.t >= j.b && i.t <= j.t) || (i.b >= j.b && i.b <= j.t)) return true;
		if ((j.t >= i.b && j.t <= i.t) || (j.b >= i.b && j.b <= i.t)) return true;
	}
	return false;
}

vector<int> getAdj(rec r){
	vector<int> cur, ans;
	cur = bot[r.t];
	for(int i=0; i<(int)cur.size(); i++){
		if (areAdj(r, vet[cur[i]])) ans.push_back(cur[i]);
	}
	cur = top[r.b];
	for(int i=0; i<(int)cur.size(); i++){
		if (areAdj(r, vet[cur[i]])) ans.push_back(cur[i]);
	}
	cur = lef[r.r];
	for(int i=0; i<(int)cur.size(); i++){
		if (areAdj(r, vet[cur[i]])) ans.push_back(cur[i]);
	}
	cur = rig[r.l];
	for(int i=0; i<(int)cur.size(); i++){
		if (areAdj(r, vet[cur[i]])) ans.push_back(cur[i]);
	}
	return ans;
}

int dfs(int u){
	if (vis[u]) return 0;
	vis[u] = true;
	int ans = vet[u].area();
	for(int i=0, v; i<(int)adjList[u].size(); i++){
		v = adjList[u][i];
		ans += dfs(v);
	}
	return ans;
}

int main()
{
	int N, l, r, b, t, u, v;
	scanf("%d", &N);
	vector<int> curadjlist;
	rec cur;
	for(int i=0; i<N; i++){
		scanf("%d %d %d %d", &l, &b, &r, &t);
		t += b;
		r += l;
		cur.t = t;
		cur.b = b;
		cur.l = l;
		cur.r = r;
		bot[b].push_back(i);
		top[t].push_back(i);
		rig[r].push_back(i);
		lef[l].push_back(i);
		vet[i] = cur;
		curadjlist = getAdj(cur);
		for(int j=0; j<(int)curadjlist.size(); j++){
			u = i;
			v = curadjlist[j];
			adjList[u].push_back(v);
			adjList[v].push_back(u);
		}
	}
	memset(&vis, false, sizeof vis);
	int ans = 0;
	for(int i=0; i<N; i++){
		if (!vis[i]) ans = max(ans, dfs(i));
	}
	printf("%d\n", ans);
	return 0;
}