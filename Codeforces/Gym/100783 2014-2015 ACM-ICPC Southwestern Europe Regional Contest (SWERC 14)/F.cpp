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
map<int, vector<int> > bot, top, lef, rig;

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

bool tcomp(int i, int j){
	return vet[i].t < vet[j].t;
}

bool rcomp(int i, int j){
	return vet[i].r < vet[j].r;
}

int main()
{
	int N, l, r, b, t, u, v;
	scanf("%d", &N);
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
	}
	
	map<int, vector<int> >::iterator it;
	
	for(it = top.begin(); it!=top.end(); it++){
		if (!bot.count(it->first)) continue;
		vector<int> &A = it->second;
		sort(A.begin(), A.end(), &rcomp);
		vector<int> &B = bot[it->first];
		sort(B.begin(), B.end(), &rcomp);
		int i=0, j=0, u, v;
		while(i < (int)A.size() && j < (int)B.size()){
			u = A[i]; v = B[j];
			if (areAdj(vet[u], vet[v])){
				adjList[u].push_back(v);
				adjList[v].push_back(u);
			}
			if (vet[u].r <= vet[v].r && i+1 < (int)A.size()) i++;
			else if (vet[u].r >= vet[v].r && j+1 < (int)B.size()) j++;
			else break;
		}
	}
	
	for(it = lef.begin(); it!=lef.end(); it++){
		if (!rig.count(it->first)) continue;
		vector<int> &A = it->second;
		sort(A.begin(), A.end(), &tcomp);
		vector<int> &B = rig[it->first];
		sort(B.begin(), B.end(), &tcomp);
		int i=0, j=0, u, v;
		while(i < (int)A.size() && j < (int)B.size()){
			u = A[i]; v = B[j];
			if (areAdj(vet[u], vet[v])){
				adjList[u].push_back(v);
				adjList[v].push_back(u);
			}
			if (vet[u].t <= vet[v].t && i+1 < (int)A.size()) i++;
			else if (vet[u].t >= vet[v].t && j+1 < (int)B.size()) j++;
			else break;
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