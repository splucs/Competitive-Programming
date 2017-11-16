#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009

typedef long long int ll;
typedef pair<int, int> ii;

/*
 * ALGORITMO DE MO
 */
int arr[MAXN], N, sn, Q;
bool appeared[MAXN];
int inv[MAXN];	//mo tree

struct query {
	int l, r, id, lca;
	int ans, tot;
	query() { l=r=id=lca=-1; }
	query(int _id, int _l, int _r){
		id = _id; l = _l; r = _r; lca = -1;
	}
} qrs[MAXN];
bool lrcomp(query a, query b){
	if (a.l/sn != b.l/sn) return a.l/sn < b.l/sn;
  	return a.r > b.r;
}
bool idcomp(query a, query b){
	return a.id < b.id;
}

int freq[MAXN], curTot, freqs[MAXN], maxfreqs;
void check(int i) {
	if (i < 0 || i>= N) return;
	if (appeared[inv[i]]) {	//mo tree
		freqs[freq[arr[i]]]--;
		freq[arr[i]]--;
		curTot--;
		freqs[freq[arr[i]]]++;
		if (freqs[maxfreqs] == 0) maxfreqs--;
	}
	else {
		freqs[freq[arr[i]]]--;
		freq[arr[i]]++;
		curTot++;
		freqs[freq[arr[i]]]++;
		maxfreqs = max(maxfreqs, freq[arr[i]]);
	}
	appeared[inv[i]] = !appeared[inv[i]];	//mo tree
}

void mo(){
	sn = sqrt(N);
	sort(qrs, qrs+Q, &lrcomp);
	memset(&freq, 0, sizeof freq);
	memset(&freqs, 0, sizeof freqs);
	maxfreqs = 0;
	int l = 1, r = 0;
	curTot = 0;
	for(int i=0; i<Q; i++){
		query & q = qrs[i];
		while(r > q.r) check(r--);
		while(r < q.r) check(++r);
		while(l < q.l) check(l++);
		while(l > q.l) check(--l);
		q.ans = maxfreqs;
		q.tot = curTot;
	}
	sort(qrs, qrs+Q, &idcomp);
}

/*
 * LCA
 */
#include <vector>
#define MAXLOGN 20
 
vector<ii> adjList[MAXN];
int depth[MAXN], level[MAXN];
int P[MAXN][MAXLOGN];

void depthdfs(int u){
	for(int i=0; i<(int)adjList[u].size(); i++){
		int v = adjList[u][i].first;
		int w = adjList[u][i].second;
		if (v == P[u][0]) continue;
		P[v][0] = u;
		level[v] = 1 + level[u];
		depth[v] = w + depth[u];
		depthdfs(v);
	}
}
void computeP(int root){
	level[root] = depth[root] = 0;
	P[root][0] = root;
	depthdfs(root);
	for(int j = 1; j < MAXLOGN; j++)
		for(int i = 1; i <= N; i++)
			P[i][j] = P[P[i][j-1]][j-1];
}
int LCA(int a, int b){
	if(level[a] > level[b]) swap(a, b);
	int d = level[b] - level[a];
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

/*
 * TREE MO
 */

int st[MAXN], en[MAXN], cnt, c[MAXN];
void prepos(int u, int p) {
	arr[cnt] = c[u];
	inv[cnt] = u;
	st[u] = cnt++;
	for(int i=0; i<(int)adjList[u].size(); i++) {
		int v = adjList[u][i].first;
		int w = adjList[u][i].second;
		if (v == p) continue;
		c[v] = w;
		prepos(v, u);
	}
	arr[cnt] = c[u];
	inv[cnt] = u;
	en[u] = cnt++;
}
void treemo(int root) {
	cnt = 0;
	c[root] = -1;
	prepos(root, -1);
	computeP(root);
	N = cnt;
	memset(&appeared, false, sizeof appeared);
	for(int i=0, u, v, lca; i<Q; i++) {
		query & q = qrs[i];
		u = q.l; v = q.r; lca = LCA(u, v);
		if (st[u] > st[v]) swap(u, v);
		if (lca == u) q.l = st[u]+1, q.lca = -1;	//propriedade na aresta
		else q.l = en[u], q.lca = -1;
		//if (lca == u) q.l = st[u], q.lca = -1;	//propriedade no noh
		//else q.l = en[u], q.lca = st[lca];
		q.r = st[v];
	}
	mo();
}

/*
 * SPOJ COT2
 */
 
int main()
{
	scanf("%d %d", &N, &Q);
	int u, v, w;
	for(int i=1; i<N; i++) {
		scanf("%d %d %d", &u, &v, &w);
		adjList[u].push_back(ii(v, w));
		adjList[v].push_back(ii(u, w));
	}
	int l, r;
	for(int i=0; i<Q; i++){
		scanf("%d %d", &l, &r);
		qrs[i] = query(i, l, r);		
	}
	treemo(1);
	for(int i=0; i<Q; i++){
		printf("%.10f\n", qrs[i].ans*100.0/qrs[i].tot);
	}
	return 0;
}