#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < int(n); i++)
#define FOR1(i, n) for(int i = 1; i <= int(n); i++)
#define MAXN 100009
#define MAXLOGN 20
#define pb push_back
#define fi first
#define se second
#define all(x) x.begin(), x.end()
typedef vector<int> vi;
typedef long long ll;
typedef pair<int, int> ii;

int n, q;
int P[MAXN][MAXLOGN], d[MAXN];
vi g[MAXN];

void dfs(int i, int h) {
	d[i] = h;
	for(int j : g[i]) dfs(j, h+1);
}

int la(int i, int h) {
	FOR(j, MAXLOGN) {
		if (h & (1<<j)) i = P[i][j];
	}
	return i;
}

int main() {
	scanf("%d %d", &n, &q);
	FOR(i, n) {
		int j;
		scanf("%d", &j);
		if (j == -1) P[i][0] = i;
		else {
			g[j].pb(i);
			P[i][0] = j;
		}
	}
	FOR(i, n) if (P[i][0] == i) dfs(i, 1);
	FOR1(j, MAXLOGN-1) {
		FOR(i, n) {
			P[i][j] = P[P[i][j-1]][j-1];
		}
	}
	while(q --> 0) {
		int i, j;
		scanf("%d %d", &i, &j);
		if (d[i] >= d[j] && la(i, d[i]-d[j]) == j) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}