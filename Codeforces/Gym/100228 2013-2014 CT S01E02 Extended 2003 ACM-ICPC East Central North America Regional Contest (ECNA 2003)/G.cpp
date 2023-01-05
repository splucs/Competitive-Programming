#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
#define MAXB 209
#define MOD 1000000007ULL
#define P 87ULL

bool b[MAXB][MAXB];
int ans1, ans2;

struct node {
	int sz, tot, dep;
	unsigned long long hsh;
	bool leaf;
	vector<unsigned long long> mask;
} nds[MAXN];

void build(const int p, const int i, const int j, const int sz) {
	node & n = nds[p];
	n.sz = sz;
	n.mask.resize(sz);
	n.mask.assign(sz, 0);
	if (sz == 1) {
		n.mask[0] = b[i][j];
		n.tot = b[i][j] ? 1 : 0;
		n.dep = 1;
		n.leaf = true;
	}
	else {
		n.tot = 0;
		n.dep = 0;
		for(int l=0; l<2; l++) for(int r=0; r<2; r++) {
			int pl = 4*(p+1) + 2*l + r;
			build(pl, i + l*sz/2, j + r*sz/2, sz/2);
			node & nl = nds[pl];
			n.dep = max(n.dep, 2*nl.dep);
			for(int it=0; it<sz/2; it++) {
				n.mask[it+l*sz/2] |= (nl.mask[it] << (r*sz/2));
			}
			n.tot += nl.tot;
		}
		n.leaf = (n.tot == 0 || n.tot == sz*sz);
		if (n.leaf) n.dep = 1;
	}
	int r = sz/n.dep;
	n.hsh = 0;
	unsigned long long pr = 1;
	for(int i=0; i<sz; i+=r) {
		unsigned long long cur = 0;
		for(int j=0; j<sz; j+=r)
			if ((1ULL << j) & n.mask[i])
				cur |= (1ULL << (j/r));
		n.hsh = (n.hsh + (cur%MOD)*pr)%MOD;
		pr = (pr*P)%MOD;
		n.hsh = (n.hsh + ((cur >> (n.dep/2))%MOD)*pr)%MOD;
		pr = (pr*P)%MOD;
	}
	//printf("building node %d, sz = %d, dep = %d, hash = %I64u\n", p, sz, n.dep, n.hsh);
}

struct cmp {
	int id;
	cmp(int _id) : id(_id) {}
};

bool operator < (const cmp na, const cmp nb) {
	node & a = nds[na.id];
	node & b = nds[nb.id];
	if (a.dep != b.dep) return a.dep < b.dep;
	if (a.leaf) return na.id < nb.id;
	return a.hsh < b.hsh;
}

set<cmp> all;

void dfs(int p, bool in) {
	ans1++;
	if(in && all.count(cmp(p))) in = false;
	if(in) all.insert(cmp(p));
	node & n = nds[p];
	if (n.leaf) return;
	for(int l=0; l<2; l++) for(int r=0; r<2; r++) {
		int pl = 4*(p+1) + 2*l + r;
		dfs(pl, in);
	}
}

char buffer[MAXN];

int main() {
	int N, M;
	while(scanf("%d %d", &N, &M), N||M) {
		memset(&b, false, sizeof b);
		for(int i=0; i<N; i++) {
			scanf(" %s", buffer);
			for(int j=0; j<M; j++) b[i][j] = buffer[j] == '1';
		}
		if (N + M == 2) {
			printf("1 1\n");
			continue;
		}
		int sz = 1;
		while (sz < N || sz < M) sz *= 2;
		ans1 = ans2 = 0;
		build(0, 0, 0, sz/2);
		build(1, 0, sz/2, sz/2);
		build(2, sz/2, 0, sz/2);
		build(3, sz/2, sz/2, sz/2);
		all.clear();
		dfs(0, true);
		dfs(1, true);
		dfs(2, true);
		dfs(3, true);
		ans2 = all.size();
		if (nds[0].tot + nds[1].tot + nds[2].tot + nds[3].tot == 0 || nds[0].tot + nds[1].tot + nds[2].tot + nds[3].tot == sz*sz)
			ans1 = ans2 = 0;
		printf("%d %d\n", ans1+1, ans2+1);
	}
	return 0;
}