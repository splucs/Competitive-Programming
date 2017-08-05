#include <bits/stdc++.h>
using namespace std;
#define MAXN 150009

typedef long long ll;

const ll neutral = 0;
ll comp(ll a, ll b){
	return a+b;
}

class FenwickTree {
private:
	vector<ll> ft;
public:
	FenwickTree(int n) {
		ft.assign(n + 1, 0);	//1-indexed
	}
	ll rsq(int i) { // returns RSQ(1, i)
		ll sum = neutral;
		while(i > 0){
			sum = comp(sum, ft[i]);
			i -= (i & -i);
		}
		return sum;
	}
	ll rsq(int i, int j){
		return rsq(j) - rsq(i - 1);
	}
	void update(int i, ll v) {
		while(i < (int)ft.size()) {
			ft[i] = comp(v, ft[i]);
			i += (i & -i);
		}
	}
};

map<ll, int> v2id;
set<ll> allf;
map<ll, int> curf;
int N, M, k[MAXN];
ll f[MAXN], q[MAXN];
FenwickTree ft(MAXN);

void printcurf() {
	map<ll, int>::iterator it = curf.begin();
	printf("curf:");
	for(; it != curf.end(); it++) {
		printf(" %I64d[%d]", it->first, it->second);
	}
	printf("\n");
}

int query() {
	//printcurf();
	if (N <= 2) return N;
	int ans = 2;
	map<ll, int>::iterator it = curf.begin();
	ll S = it->first;
	if (it->second == 1) it++;
	S += it->first;
	//printf("S = %I64d\n", S);
	while((it = curf.lower_bound(S)) != curf.end()) {
		ll f = it->first;
		ll sum = ft.rsq(v2id[f]-1);
		//printf("f = %I64d sum = %I64d\n", f, sum);
		if (sum <= f) ans++;
		S = sum + f;
		//printf("S = %I64d\n", S);
	}
	return ans;
}

int main()
{
	scanf("%d", &N);
	for(int i=1; i<=N; i++) {
		scanf("%I64d", &f[i]);
		allf.insert(f[i]);
		if (curf.count(f[i])) curf[f[i]]++;
		else curf[f[i]] = 1;
	}
	scanf("%d", &M);
	for(int i=1; i<=M; i++){
		scanf("%d %I64d", &k[i], &q[i]);
		allf.insert(q[i]);
	}
	int id = 1;
	for(set<ll>::iterator it = allf.begin(); it != allf.end(); it++) {
		v2id[*it] = id++;
	}
	for(int i=1; i<=N; i++) {
		ft.update(v2id[f[i]], f[i]);
	}
	printf("%d\n", query());
	for(int i=1; i<=M; i++) {
		int j = k[i];
		//printf("removing %I64d and adding %I64d\n", f[j], q[i]);
		ft.update(v2id[f[j]], -f[j]);
		curf[f[j]]--;
		if (curf[f[j]] == 0) curf.erase(f[j]);
		f[j] = q[i];
		ft.update(v2id[q[i]], f[j]);
		if (curf.count(f[j])) curf[f[j]]++;
		else curf[f[j]] = 1;
		printf("%d\n", query());
	}
	return 0;
}