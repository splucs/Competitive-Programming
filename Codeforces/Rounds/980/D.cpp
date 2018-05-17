#include <bits/stdc++.h>
using namespace std;
#define MAXN 5009
#define MAXM (30*MAXN)
#define MOD 1000000007
#define INF 1000000009
#define EPS 1e-9
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define pb push_back
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;
#define EPS 1e-9

vector<ii> fac[MAXN];
ll a[MAXN];
int n;

vector<ii> decompose(ll N) {
	N = abs(N);
	vector<ii> ans;
	for(int i = 2; i*1ll*i <= N; i++) {
		if (N % i == 0) {
			ans.pb({i, 0});
			while(N % i == 0) {
				ans.back().second ^= 1;
				N /= i;
			}
		}
	}
	if (N > 1) ans.pb({N, 1});
	return ans;
}

void preprocess() {
	FOR(i, n) {
		fac[i] = decompose(a[i]);
	}
}

bool comp(int id1, int id2) {
	if (a[id1]*a[id2] < 0) return a[id1] < a[id2];
	if (a[id2] == 0 && a[id1] < 0) return true;
	if (a[id1] == 0 && a[id2] < 0) return false;
	vector<ii> & f1 = fac[id1];
	vector<ii> & f2 = fac[id2];
	int i = 0, j = 0;
	while(i < int(f1.size()) && j < int(f2.size())) {
		if (f1[i].first < f2[j].first) {
			if (f1[i].second) return false;
			i++;
		}
		else if (f1[i].first > f2[j].first) {
			if (f2[j].second) return true;
			j++;
		}
		else {
			if ((f1[i].second) != (f2[j].second))
				return (f1[i].second) < (f2[j].second);
			i++; j++;
		}
	}
	while (i < int(f1.size())) {
		if (f1[i].second) return false;
		i++;
	}
	while (j < int(f2.size())) {
		if (f2[j].second) return true;
		j++;
	}
	return false;
}

int id[MAXN], key[MAXN];
int app[MAXN], ans[MAXN];

int main() {
	scanf("%d", &n);
	FOR(i, n) {
		scanf("%I64d", &a[i]);
		id[i] = i;
	}
	preprocess();
	sort(id, id+n, comp);
	key[id[0]] = 0;
	int cnt = 1;
	FOR1(i, n-1) {
		if (comp(id[i-1], id[i])) {
			key[id[i]] = 1 + key[id[i-1]];
			cnt++;
		}
		else key[id[i]] = key[id[i-1]];
		//printf("key[%d] = %d\n", id[i], key[id[i]]);
	}
	FOR1(i, n) ans[i] = 0;
	FOR(i, n) {
		FOR(it, cnt) {
			app[it] = 0;
		}
		int cur = 0;
		for(int j = i; j < n; j++) {
			if (a[j] != 0) {
				app[key[j]]++;
				if (app[key[j]] == 1) cur++;
			}
			//printf("(%d,%d) -> %d\n", i, j, cur);
			ans[max(cur, 1)]++;
		}
	}
	FOR1(i, n) printf("%d ", ans[i]);
	printf("\n");
	return 0;
}