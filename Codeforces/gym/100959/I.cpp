#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define INF (1LL << 60)

typedef long long ll;
map<ll, map<ll, int> > xy, yx;
char dir[MAXN];
ll T[MAXN], qT, x[MAXN], y[MAXN];

int n;

void remove(int u) {
	xy[x[u]].erase(y[u]);
	if (xy[x[u]].empty()) xy.erase(x[u]);
	yx[y[u]].erase(x[u]);
	if (yx[y[u]].empty()) yx.erase(y[u]);
}

int main()
{
	scanf("%d %I64d", &n, &qT);
	for(int i=1; i<=n; i++) {
		scanf("%I64d %I64d %c", &x[i], &y[i], &dir[i]);
		xy[x[i]][y[i]] = i;
		yx[y[i]][x[i]] = i;
		T[i] = INF;
	}
	queue<int> q;
	stack<int> tr;
	q.push(1);
	T[1] = 0;
	remove(1);
	map<ll, map<ll, int> >::iterator it1;
	map<ll, int>::iterator fi;
	map<ll, int>::reverse_iterator ri;
	while(!q.empty()){
		int u = q.front();
		q.pop();
		printf("analysing %d, T[%d] = %I64d\n", u, u, T[u]);
		if (dir[u] == 'U'){
			it1 = xy.find(x[u]);
			if (it1 == xy.end()) continue;
			for(ri = it1->second.rbegin(); ri!=it1->second.rend() && ri->first > y[u]; ri++){
				tr.push(ri->second);
			}
		}
		if (dir[u] == 'D'){
			it1 = xy.find(x[u]);
			if (it1 == xy.end()) continue;
			for(fi = it1->second.begin(); fi!=it1->second.end() && fi->first < y[u]; fi++){
				tr.push(fi->second);
			}
		}
		if (dir[u] == 'L'){
			it1 = yx.find(y[u]);
			if (it1 == yx.end()) continue;
			for(fi = it1->second.begin(); fi!=it1->second.end() && fi->first < x[u]; fi++){
				tr.push(fi->second);
			}
		}
		if (dir[u] == 'R'){
			it1 = yx.find(y[u]);
			if (it1 == yx.end()) continue;
			for(ri = it1->second.rbegin(); ri!=it1->second.rend() && ri->first > x[u]; ri++){
				tr.push(ri->second);
			}
		}
		while(!tr.empty()) {
			int v = tr.top();
			printf("reaches %d\n", v);
			tr.pop();
			q.push(v);
			remove(v);
			T[v] = abs(x[u] - x[v]) + abs(y[u] - y[v]) + T[u];
		}
	}
	for(int i=1; i<=n; i++){
		if (T[i] <= qT && dir[i] == 'U') y[i] += qT - T[i];
		if (T[i] <= qT && dir[i] == 'D') y[i] -= qT - T[i];
		if (T[i] <= qT && dir[i] == 'R') x[i] += qT - T[i];
		if (T[i] <= qT && dir[i] == 'L') x[i] -= qT - T[i];
		printf("T[%d] = %I64d\n", i, T[i]);
		printf("%I64d %I64d\n", x[i], y[i]);
	}
	return 0;
}