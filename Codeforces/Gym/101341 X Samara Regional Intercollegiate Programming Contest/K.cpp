#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
#define state dp[i]
#define INF (1<<30)

typedef long long ll;
typedef pair<ll, ll> ii;

struct contest{
	ll s, t, p;
	int id;
};

contest v[MAXN];

bool operator < (contest a, contest b) {
	return a.s < b.s;
}

ii operator + (ii a, ii b){
	return ii(a.first+b.first, a.second+b.second);
}

int N;
vector<int> adj[MAXN];
ii dp[MAXN];
int A[MAXN], C[MAXN];
map<ll, ll> x2id;
ll id2x[MAXN];
int nid = 0;

int find(ll x){
	if (x > id2x[nid-1]) return INF;
	int ans = x2id.lower_bound(x)->second;
	//printf("find(%I64d)=%d\n", x, ans);
	return ans;
}

ii DP(const int i){
	if (i >= nid) return ii(0, 0ll);
	if (state.first >= 0) return state;
	vector<int> & id = adj[i];
	state = DP(i+1);
	A[i] = i+1;
	C[i] = -1;
	//printf("dp[%d] = (%I64d,%I64d),%d\n", i, state.first, -state.second, A[i]);
	for(int j=0; j<(int)id.size(); j++){
		int c = id[j];
		ii cur = ii(v[c].p, v[c].s - v[c].t) + DP(find(v[c].t));
		if(state < cur){
			state = cur;
			A[i] = find(v[c].t);
			C[i] = c;
		}
	//printf("dp[%d] = (%I64d,%I64d),%d\n", i, state.first, -state.second, A[i]);
	}
	return state;
}

int main() {
	scanf("%d", &N);
	for(int i=1; i<=N; i++){
		scanf("%I64d %I64d %I64d", &v[i].s, &v[i].t, &v[i].p);
		v[i].id = i;
	}
	sort(v+1, v+1+N);
	for(int i=1; i<=N; i++){
		ll s = v[i].s;
		if (!x2id.count(s)){
			id2x[nid] = s;
			x2id[s] = nid++;
		}
		adj[x2id[s]].push_back(i);
		//printf("(%I64d,%I64d,%I64d)\n", v[i].s, v[i].t, v[i].p);
	}
	/*for(int i=0; i<nid; i++){
		printf("id %d(%I64d)\n", i, id2x[i]);
		for(int j=0; j<(int)adj[i].size(); j++){
			printf("%d ", adj[i][j]);
		}
		printf("\n");
	}
	for(ll x=0; x<10ll; x++){
		printf("find(%I64d)=%d\n", x, find(x));
		
	}*/
	for(int i=0; i<nid; i++) state = ii(-1,-1);
	ii ans = DP(0);
	int i=0;
	int ncomp = 0;
	while(A[i] < INF){
		if(C[i] >= 0) ncomp++;
		i = A[i];
	}
	if(C[i] >= 0) ncomp++;
	printf("%d %I64d %I64d\n", ncomp, ans.first, -ans.second);
	i = 0;
	while(A[i] < INF){
		if(C[i] >= 0) printf("%d ", v[C[i]].id);
		i = A[i];
	}
	if(C[i] >= 0) printf("%d ", v[C[i]].id);
	printf("\n");
	return 0;
}