#include <bits/stdc++.h>
using namespace std;
#define MAXN 2000009
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back

int n, k;
int nxt[MAXN][26], link[MAXN];
int cnt[MAXN];
vector<char> g[MAXN];

int q[MAXN];

void insert(char str[]) {
	int len = strlen(str);
	int u = 0;
	FOR(i, len) {
		int c = str[i] - 'A';
		if (nxt[u][c] == 0) {
			nxt[u][c] = ++n;
			g[u].pb(c);
		}
		u = nxt[u][c];
	}
}

void aho() {
	int en = 0;
	for (char c : g[0]) {
		int u = nxt[0][c];
		link[u] = 0;
		q[en++] = u;
	}
	FOR(st, en) {
		int u = q[st];
		for (char c : g[u]) {
			int v = nxt[u][c];
			int w = link[u];
			while(w != 0 && nxt[w][c] == 0) w = link[w];
			link[v] = nxt[w][c];
			q[en++] = v;
		}
	}
	REP(i, en) {
		int u = q[i];
		cnt[link[u]] += cnt[u];
	}
}

int go(const char str[]) {
	int len = strlen(str);
	int u = 0;
	FOR(i, len) {
		char c = str[i] - 'A';
		if (nxt[u][c] == 0) return 0;
		u = nxt[u][c];
	}
	return cnt[u];
}

char str[MAXN];
int st[MAXN];

int main () {
	scanf("%d %d", &n, &k);
	FOR1(v, n) {
		int u;
		char c;
		scanf(" %c %d", &c, &u);
		c -= 'A';
		nxt[u][c] = v;
		g[u].pb(c);
		cnt[v] = 1;
	}
	st[0] = 0;
	FOR(i, k) {
		scanf(" %s", str+st[i]);
		int len = strlen(str+st[i]);
		reverse(str+st[i], str+st[i]+len);
		insert(str+st[i]);
		st[i+1] = st[i]+len+1;
	}
	aho();
	FOR(i, k) {
		printf("%d\n", go(str+st[i]));
	}
	return 0;
}