/*
             /\\
              .\\\..
              \\   \\
              \ (o) /
              (/    \
               /\    \
              ///     \
             ///|     |
            ////|     |
           //////    /
           |////    /
          /|////--V/  Stephen Morgana
         //\//|   |
     ___////__\___\__________
    ()_________'___'_________)
        \\\\
          \\\
            \\
*/

#include <bits/stdc++.h>
#define DEBUG false
#define debugf if (DEBUG) printf
#define MAXN 100309
#define MAXM 300009
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define EPS 1e-9
#define PI 3.141592653589793238462643383279502884
#define FOR(x,n) for(int x=0; (x)<int(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=int(n); (x)++)
#define REP(x,n) for(int x=int(n)-1; (x)>=0; (x)--)
#define REP1(x,n) for(int x=(n); (x)>0; (x)--)
#define pb push_back
#define pf push_front
#define fi first
#define se second
#define mp make_pair
#define all(x) x.begin(), x.end()
#define mset(x,y) memset(&x, (y), sizeof(x));
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef unsigned int uint;

class UnionFind {
private:
	vector<int> parent, rank, sz;
public:
	UnionFind(int N) {
		rank.assign(N+1, 0);
		parent.assign(N+1, 0);
		sz.assign(N+1, 1);
		for (int i = 0; i <= N; i++) parent[i] = i;
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
		if (rank[x] > rank[y]) {
			parent[y] = x;
			sz[x] += sz[y];
		}
		else {
			parent[x] = y;
			sz[y] += sz[x];
			if (rank[x] == rank[y]) rank[y]++;
		}
	}
	int size(int i) { return sz[find(i)]; }
};

int id[MAXN], n, arr[MAXN];
bool stop[MAXN];

bool comp(int i, int j) {
	return arr[i] < arr[j];
}

int main() {
	scanf("%d", &n);
	UnionFind uf(n);
	FOR(i, n) {
		id[i] = i;
		scanf("%d", &arr[i]);
	}
	sort(id, id+n, comp);
	map<int, int> cnt;
	ii ans = ii(-1, 0);
	mset(stop, false);
	FOR(it, n) {
		int i = id[it];
		stop[i] = true;
		cnt[1]++;
		if (i > 0 && stop[i-1]) {
			cnt[uf.size(i-1)]--;
			cnt[uf.size(i)]--;
			uf.unionSet(i, i-1);
			cnt[uf.size(i)]++;
		}
		if (i+1 < n && stop[i+1]) {
			cnt[uf.size(i+1)]--;
			cnt[uf.size(i)]--;
			uf.unionSet(i, i+1);
			cnt[uf.size(i)]++;
		}
		int sz = uf.size(i);
		if (sz*cnt[sz] == (it+1)) {
			int k = arr[i]+1;
			ans = max(ans, ii((it+1)/sz, -k));
		}
	}
	printf("%d\n", -ans.se);
	return 0;
}