#include <bits/stdc++.h>
using namespace std;
#define MOD 13
#define MAXN 209
#define INF (1<<30)

template <typename T>
T extGcd(T a, T b, T& x, T& y) {
    if (b == 0) {
        x = 1; y = 0;
        return a;
    }
    else {
        T g = extGcd(b, a % b, y, x);
        y -= a / b * x;
        return g;
    }
}
 
template <typename T>
T modInv(T a, T m) {
    T x, y;
    extGcd(a, m, x, y);
    return (x % m + m) % m;
}

typedef vector< vector< int > > matrix;
int N, s, t, n, m, d, p;
int adjmap[MAXN][MAXN];
int way[4*MAXN], x[MAXN];
int minv[MOD];
matrix a, b;

void switchLines(matrix & a, int i, int j){
	int tmp;
	int m = (int)a[i].size();
	for(int k=0; k<m; k++){
		tmp = a[i][k];
		a[i][k] = a[j][k];
		a[j][k] = tmp;
	}
}

void lineSumTo(matrix & a, int i, int j, int c){
	int m = (int)a[j].size();
	for(int k=0; k<m; k++){
		a[j][k] = (a[j][k] + c*a[i][k]) % MOD;
	}
}

bool gauss(matrix & a, matrix & b){
	int n = (int)a.size();
	int m = (int)a[0].size();
	int p;
	for(int i = 0, l; i < min(n, m); i++){
		l = i;
		while(l < n && a[l][i] == 0) l++;
		if (l == n) return false;
		switchLines(a, i, l);
		switchLines(b, i, l);
		for(int j=i+1; j<n; j++){
			p = ((MOD-a[j][i])*modInv(a[i][i], MOD)) % MOD;
			lineSumTo(a, i, j, p);
			lineSumTo(b, i, j, p);
		}
	}
	for(int i=min(n, m)-1; i>=0; i--){
		for(int j=0; j<i; j++){
			p = ((MOD-a[j][i])*modInv(a[i][i], MOD)) % MOD;
			lineSumTo(a, i, j, p);
			lineSumTo(b, i, j, p);
		}
	}
	return true;
}

void printAB() {
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++) {
			printf("%d ", a[i][j]);
		}
		printf(" : %d\n", b[i][0]);
	}
}

typedef pair<int, int> ii;
vector<ii> adjList[MAXN];
int dist[MAXN];

int dijkstra(int s, int t)
{
	for(int i=1; i<=N; i++) dist[i] = INF;
	dist[s]=0;
	set<pair<int, int> > nodes;
	nodes.insert(ii(0, s));
	while(!nodes.empty()){
		int u = nodes.begin()->second;
		nodes.erase(nodes.begin());
		for(int i=0; i<(int)adjList[u].size(); i++){
			int v = adjList[u][i].second;
			int w = adjList[u][i].first;
			if (dist[v] > dist[u] + w){
				if (dist[v] < INF){
					nodes.erase(ii(dist[v], v));
				}
				dist[v] = dist[u] + w;
				nodes.insert(ii(dist[v], v));
			}
		}
	}
	return dist[t];
}

int main() {
	for(int i=0; i<MOD; i++) minv[i] = modInv(i, MOD);
	scanf("%d %d %d %d", &N, &s, &t, &n);
	a.resize(n);
	for(int i=0; i<n; i++) {
		a[i].resize(MAXN);
	}
	b.resize(n);
	memset(&adjmap, -1, sizeof adjmap);
	m = 0;
	for(int i=0; i<n; i++) {
		scanf("%d %d", &d, &p);
		b[i].push_back(d);
		for(int j=0; j<p; j++) {
			scanf("%d", &way[j]);
			if (j > 0){
				int u = way[j-1];
				int v = way[j];
				if (u == v) continue;
				if (adjmap[u][v] < 0){
					adjmap[u][v] = adjmap[v][u] = m++;
					//printf("(%d,%d)->%d\n", u, v, m-1);
				}
				a[i][adjmap[u][v]]++;
				a[i][adjmap[u][v]] %= MOD;
			}
		}
	}
	for(int i=0; i<n; i++) a[i].resize(m);
	//printAB();
	if (!gauss(a, b)) {
		printf("%d\n", 13*300);
		return 0;
	}
	//printf("\n");
	//printAB();
	for(int i=0; i<n; i++) {
		x[i] = (b[i][0]*modInv(a[i][i], MOD)) % MOD;
		//printf("x[%d] = %d\n", i, x[i]);
	}
	for(int u=1; u<=N; u++) {
		for(int v=1; v<=N; v++){
			if (adjmap[u][v] >= 0)
				adjList[u].push_back(ii(x[adjmap[u][v]], v));
		}
	}
	printf("%d\n", dijkstra(s, t));
	return 0;
}