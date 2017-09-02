#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009

class FenwickTree {
private:
	vector<int> ft;
public:
	FenwickTree(int n) {
		ft.assign(n + 1, 0);	//1-indexed
	}
	int rsq(int i) { // returns RSQ(1, i)
		int sum = 0;
		while(i > 0){
			sum += ft[i];
			i -= (i & -i);
		}
		return sum;
	}
	int rsq(int i, int j){
		return rsq(j) - rsq(i - 1);
	}
	void update(int i, int v) {
		while(i < (int)ft.size()) {
			ft[i] += v;
			i += (i & -i);
		}
	}
};

struct query {
	char op;
	int e, p, a, b;
} qrs[MAXN];

int N, Q, root[MAXN], pos[MAXN], cnt;
vector<int> adjList[MAXN];

map<int, int> x2id;
int msz = 0;
inline int reduce(int x) {
	if (!x2id.count(x)) {
		x2id[x] = ++msz;
	}
	return x2id[x];
}

void dfs(int u) {
	pos[u] = ++cnt;
	for(int i=((int)adjList[u].size())-1; i>=0; i--) {
		int v = adjList[u][i];
		dfs(v);
	}
}

int main() {
	scanf("%d", &N);
	for(int i=0; i<N; i++) {
		scanf("%d", &root[i]);
		root[i] = reduce(root[i]);
	}
	scanf("%d", &Q);
	for(int j=0; j<Q; j++) {
		scanf(" %c", &qrs[j].op);
		if (qrs[j].op == 'I' || qrs[j].op == 'i') {
			int p, e;
			scanf("%d %d", &p, &e);
			p = reduce(p);
			e = reduce(e);
			adjList[e].push_back(p);
			qrs[j].p = p;
			qrs[j].e = e;
		}
		else if (qrs[j].op == 'R' || qrs[j].op == 'r') {
			int e;
			scanf("%d", &e);
			qrs[j].e = reduce(e);
			x2id.erase(e);
		}
		else if (qrs[j].op == 'Q' || qrs[j].op == 'q') {
			int a, b;
			scanf("%d %d", &a, &b);
			qrs[j].a = reduce(a);
			qrs[j].b = reduce(b);
		}
	}
	cnt = 0;
	for(int i=0; i<N; i++) {
		dfs(root[i]);
	}
	FenwickTree ft(cnt);
	for(int i=0; i<N; i++) {
		ft.update(pos[root[i]], 1);
	}
	for(int j=0; j<Q; j++) {
		if (qrs[j].op == 'I' || qrs[j].op == 'i') {
			ft.update(pos[qrs[j].p], 1);
		}
		else if (qrs[j].op == 'R' || qrs[j].op == 'r') {
			ft.update(pos[qrs[j].e], -1);
		}
		else if (qrs[j].op == 'Q' || qrs[j].op == 'q') {
			int l = pos[qrs[j].a];
			int r = pos[qrs[j].b];
			if (l > r) swap(l, r);
			printf("%d\n", ft.rsq(l, r)-2);
		}
	}
	return 0;
}