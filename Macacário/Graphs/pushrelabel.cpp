#include <cstring>
#include <cstdio>
#define MAXN 103009
#define MAXM 900000
#define INF 0x3f3f3f3f

/*
 * Push Relabel Algorithm - O(VE + sqrt(E)V^2)
 */

int ned, first[MAXN], exc[MAXN], maxhgt[MAXN];
int cap[MAXM], to[MAXM], nxt[MAXM], hgt[MAXN];

void init() {
   memset(first, -1, sizeof first);
   ned = 0;
}

void add(int u, int v, int f) {
	to[ned] = v, cap[ned] = f;
	nxt[ned] = first[u];
	first[u] = ned++;
	
	to[ned] = u, cap[ned] = 0;
	nxt[ned] = first[v];
	first[v] = ned++;
}

void push(int e) {
	int u = to[e^1], v = to[e];
	int f = exc[u] < cap[e] ? exc[u] : cap[e];
	cap[e] -= f; cap[e^1] += f;
	exc[u] -= f; exc[v] += f;
}

void relabel(int u) {
	int f = INF;
	for (int e = first[u]; e != -1; e = nxt[e]) {
		if (cap[e] > 0 && hgt[to[e]] < f) f = hgt[to[e]];
	}
	if (f < INF) hgt[u] = f + 1;
}

int maxHeight(int s, int t, int n) {
	int sz = 0;
	for (int u = 1; u <= n; u++) {
		if (u == s || u == t || exc[u] == 0) continue;
		if (sz > 0 && hgt[u] > hgt[maxhgt[0]]) sz = 0;
		if (sz == 0 || hgt[u] == hgt[maxhgt[0]])
			maxhgt[sz++] = u;
	}
	return sz;
}

int pushrelabel(int s, int t, int n) {
	memset(&hgt, 0, sizeof hgt);
	memset(&exc, 0, sizeof exc);
	hgt[s] = n; exc[s] = INF;
	for (int e = first[s]; e != -1; e = nxt[e])
		push(e);
	int sz;
	while ((sz = maxHeight(s, t, n)) > 0) {
		for(int i = 0; i < sz; i++) {
			int u = maxhgt[i], pushed = 0;
			for (int e = first[u]; e != -1 && exc[u]; e = nxt[e]) {
				if (cap[e] > 0 && hgt[u] == hgt[to[e]] + 1)
					push(e), pushed = 1;
			}
			if (!pushed) {
				relabel(u); break;
			}
		}
	}
	return exc[t];
}

/*
 * SPOJ MTOTALF
 */

#include <cstdio>

int main() {
	int m;
	scanf("%d", &m);
	init();
	for(int j = 0; j < m; j++) {
		char u, v;
		int f;
		scanf(" %c %c %d", &u, &v, &f);
		add(u, v, f);
	}
	printf("%d\n", pushrelabel('A', 'Z', 255));
	return 0;
}