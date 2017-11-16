#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define MAXLOGN 20
#define MAXT 31
#define INF (1LL<<40)

typedef long long ll;
vector<int> adjList[MAXN];
int N, par[MAXN], K, nLeafs, depth[MAXN];
ll st[MAXN][MAXT], en[MAXN][MAXT], treesize[MAXT], koffset;
map<ll, int> inv[MAXT];
bool leaf[MAXN];
vector<int> leafs;
int P[MAXN][MAXLOGN];

void depthdfs(int u){
	for(int i=0; i<(int)adjList[u].size(); i++){
		int v = adjList[u][i];
		if (v == P[u][0]) continue;
		P[v][0] = u;
		depth[v] = 1 + depth[u];
		depthdfs(v);
	}
}

void computeP(int root){
	depth[root]=0;
	P[root][0]=root;
	depthdfs(root);
	for(int j = 1; j < MAXLOGN; j++)
		for(int i = 1; i <= N; i++)
			P[i][j] = P[P[i][j-1]][j-1];
}

int LCA(int a, int b){
	if(depth[a] > depth[b]) swap(a, b);
	int d = depth[b] - depth[a];
	for(int i=0; i<MAXLOGN; i++){
		if((d & (1<<i)) != 0) b = P[b][i];
	}
	if(a == b) return a;
	for(int i = MAXLOGN-1; i>=0; i--)
		while(P[a][i] != P[b][i]){
			a=P[a][i]; b=P[b][i];
		}
	return P[a][0];
}

void dfs(int u, ll & cnt, int t) {
	cnt = min(INF, cnt+1);
	
	st[u][t] = cnt;
	inv[t][cnt] = u;
	
	if (leaf[u] && t > 0) cnt += treesize[t-1] - 1;
	for(int i=0; i<(int)adjList[u].size(); i++) {
		int v = adjList[u][i];
		dfs(v, cnt, t);
	}
	
	en[u][t] = cnt;
	
	if (leaf[u] && t == 0) leafs.push_back(u);
}


void getpath(int t, ll k, vector<int> & path) {
	if (t == -1 || k == 0LL) return;
	
	int lo = -1;
	int hi = nLeafs;
	while(hi > lo + 1) {
		int mid = (hi + lo) / 2;
		int u = leafs[mid];
		if (st[u][t] <= k && en[u][t] >= k) {
			path.push_back(u);
			getpath(t-1, k-st[u][t]+1, path);
			return;
		}
		if (st[u][t] > k) hi = mid;
		if (en[u][t] < k) lo = mid;
	}
	
	int u = inv[t][k];
	path.push_back(u);
}

void getLCApath(const vector<int> & path1, const vector<int> & path2, vector<int> & ans) {
	ans.clear();
	for(int i=0; i<(int)path1.size() && i < (int)path2.size(); i++) {
		if (path1[i] == path2[i]) ans.push_back(path1[i]);
		else {
			//printf("LCA(%d,%d) = %d\n", path1[i], path2[i], LCA(path1[i], path2[i]));
			ans.push_back(LCA(path1[i], path2[i]));
			break;
		}
	}
}

ll getdepth(const vector<int> & path) { 
	ll ans = 0;
	for(int i=0; i<(int)path.size(); i++) {
		ans += depth[path[i]];
	}
	return ans;	
}

void printpath(ll k, const vector<int> & path, ll dep) {
	printf("path to %I64d, depth %I64d, is:", k, dep);
	for(int i=0; i<(int)path.size(); i++) {
		printf(" %d", path[i]);
	}
	printf("\n");
}

ll getdist(ll ku, ll kv) {
	vector<int> pu;
	getpath(K, ku, pu);
	//printpath(ku, pu, getdepth(pu));
	
	vector<int> pv;
	getpath(K, kv, pv);
	//printpath(kv, pv, getdepth(pv));
	
	vector<int> pl;
	getLCApath(pu, pv, pl);
	//printpath(-1, pl, getdepth(pl));
	
	return getdepth(pu) + getdepth(pv) - 2*getdepth(pl);
}

int main () {
	while (scanf("%d", &N) != EOF) {	
		par[0] = -1;
		adjList[0].clear();
		memset(&leaf, true, sizeof leaf);
		nLeafs = N;
		leafs.clear();
		
		for(int i=1; i<N; i++) {
			scanf("%d", &par[i]);
			adjList[i].clear();
			adjList[par[i]].push_back(i);
			if (leaf[par[i]]) nLeafs--;
			leaf[par[i]] = false;
		}
		scanf("%d", &K);
		
		if (nLeafs > 1) {
		
			koffset = K - MAXT+1;
			K = min(K, MAXT-1);
			treesize[0] = N;
			for(int t=1; t<=K; t++) {
				treesize[t] = min(INF, N - nLeafs + nLeafs*treesize[t-1]);
			}
			
			for(int t=0; t<=K; t++) {
				ll cnt = 0;
				inv[t].clear();
				dfs(0, cnt, t);
			}
			computeP(0);
			if (koffset < 0) koffset = 0;
			koffset *= depth[leafs[0]];
		}
		
		int Q;
		scanf("%d", &Q);
		while (Q --> 0) {
			ll ku, kv;
			scanf("%I64d %I64d", &ku, &kv);
			if (nLeafs == 1 || (ku <= koffset && kv <= koffset)) printf("%I64d\n", abs(ku-kv));
			else {
				ll ans = 0;
				if (ku <= koffset) {
					ans += koffset - ku + 1;
					ku = 1;
				}
				else ku -= koffset;
				if (kv <= koffset) {
					ans += koffset - kv + 1;
					kv = 1;
				}
				else kv -= koffset;
				
				ans += getdist(ku, kv);
				printf("%I64d\n", ans);
			}
		}
	}
	
	return 0;
}