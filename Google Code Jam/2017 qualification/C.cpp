#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> ii;

struct config{
	ll L, count;
	config(ll _L, ll _c) : L(_L), count(_c) {}
};

ll N, K;

bool operator <(config a, config b){
	return a.L > b.L;
}

ll simulate()
{
	set<config> values;
	set<config>::iterator it;
	values.insert(config(N, 1));
	config cur(0, 0);
	ll tore, prev, L, S[2];
	K--;
	while(K > 0 && !values.empty()){
		cur = *(values.begin());
		values.erase(values.begin());
		L = cur.L;
		tore = min(K, cur.count);
		//printf("%lld people go into size %lld\n", tore, L);
		K -= tore;
		if (cur.count > tore){
			cur.count -= tore;
			values.insert(cur);
		}
		if (L % 2 == 0){
			S[0] = L/2 - 1;
			S[1] = L/2;
		}
		else{
			S[0] = L/2;
			S[1] = L/2;
		}
		for(int i=0; i<2; i++){
			L = S[i];
			if (L == 0) continue;
			it = values.find(config(L, 0));
			if (it == values.end()){
				prev = 0;
			}
			else {
				prev = it->count;
				values.erase(it);
			}
			values.insert(config(L, tore+prev));
		}
	}
	return values.begin()->L;
}

int main()
{
	int T;
	scanf("%d", &T);
	ll L, S[2];
	for(int caseNo = 1; caseNo <= T; caseNo++){
		scanf("%lld %lld", &N, &K);
		L = simulate();
		if (L % 2 == 0){
			S[0] = L/2 - 1;
			S[1] = L/2;
		}
		else{
			S[0] = L/2;
			S[1] = L/2;
		}
		printf("Case #%d: %lld %lld\n", caseNo, S[1], S[0]);
	}
	return 0;
}