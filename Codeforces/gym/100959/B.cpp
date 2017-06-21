#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
#define MAXN 100009
#define INF (1LL<<40)
//#define INF 10

typedef long long ll;
ll x[MAXN], y[MAXN];
int N, idx[MAXN], idy[MAXN];

class UnionFind {
private:
	vector<int> parent, rank;
public:
	UnionFind(int N) {
		rank.assign(N, 0);
		parent.assign(N, 0);
		for (int i = 0; i < N; i++) parent[i] = i;
	}
	int find(int i) {
		while(i != parent[i]) i = parent[i];
		return i;
	}
	bool isSameSet(int i, int j) {
		return find(i) == find(j);
	}
	void unionSet (int i, int j) {
		if (isSameSet(i, j)) return;
		int x = find(i), y = find(j);
		if (rank[x] > rank[y]) parent[y] = x;
		else {
			parent[x] = y;
			if (rank[x] == rank[y]) rank[y]++;
		}
	}
};

UnionFind uf(1);

void check(int* id, ll* p, ll D){
    for(int i=N-1, j=0; i>=0; i--){
        if (abs(p[id[i]] - p[id[j]]) >= D) uf.unionSet(id[i], id[j]);
        else break;
    }
    for(int i=0, j=N-1; i<N; i++){
        if (abs(p[id[i]] - p[id[j]]) >= D) uf.unionSet(id[i], id[j]);
        else break;
    }
}

bool check(ll D) {
    uf = UnionFind(N);
    check(idx, x, D);
    check(idy, y, D);
    for(int i=0; i<N; i++){
        if (!uf.isSameSet(0, i)) return false;
    }
    return true;
}

bool compx(int i, int j) {
    if (x[i] == x[j]) return y[i] < y[j];
    return x[i] < x[j];
}

bool compy(int i, int j) {
    if (y[i] == y[j]) return x[i] < x[j];
    return y[i] < y[j];
}

int main() {
    scanf("%d", &N);
    ll xa, ya;
    for(int i=0; i<N; i++) {
        scanf("%I64d %I64d", &xa, &ya);
        x[i] = xa+ya;
        y[i] = xa-ya;
        idx[i] = idy[i] = i;
    }
    sort(idx, idx+N, &compx);
    sort(idy, idy+N, &compy);
    ll lo = 0;
    ll hi = INF;
    while(hi > lo+1) {
        ll mid = (hi+lo)/2;
        //printf("check(%I64d) = %d\n", mid, check(mid));
        if (check(mid)) lo = mid;
        else hi = mid;
    }
    printf("%I64d\n", lo);
    return 0;
}