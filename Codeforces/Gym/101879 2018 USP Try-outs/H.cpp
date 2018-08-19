#include <bits/stdc++.h>
using namespace std;

#define FOR(i, N) for (int i = 0; i < N; ++i)
#define MAXN 20009
#define pb push_back
typedef long long int ll;
typedef pair<int, int> ii;

int N, M, t[MAXN], st[MAXN], cnt[MAXN] = {}, Q;
int vals[MAXN] = {}, SQ, gqty = 0;

void add(int u, int v){
	while (u < M){
		vals[u] += v;
		u += (u & (-u));
	}
}

int qry(int u){
	int ans = 0;
	while (u){
		ans += vals[u];
		u -= (u & (-u));
	}
	return ans;
}

struct query{
	int l, r, i, ans;
};

map<int, int> conv;
vector<query> qs;

bool sort2(query q1, query q2){
	return q1.i < q2.i;
}

bool sorte(query a, query b){
	return a.l / SQ == b.l / SQ ? a.r < b.r : a.l < b.l;
}

void add2(int u){
	if (cnt[u]) add(cnt[u], -1);
	else gqty++;
	cnt[u]++;
	add(cnt[u], 1);
}

void rem(int u){
	add(cnt[u], -1);
	cnt[u]--;
	if (cnt[u]) add(cnt[u], 1);
	else --gqty;
}

int findAns(int l1, int r1){
	int l = 1, r = (sqrt(r1 - l1 + 1));
	
	//cout<<l1<<' '<<r1<<' '<<gqty<<'\n';
	//FOR(i, N + 1) if (i)cout<<qry(i) - qry(i - 1)<<' ';
	//cout<<'\n';
	
	while (l != r){
		int mid = (l + r) >> 1;
		if (gqty - qry(mid) >= mid + 1) l = mid + 1;
		else r = mid;
	}
	return l;
}

void mo(){
	int l = 0, r = -1;
	FOR(i, Q){
		query &q = qs[i];
		while (r < q.r) add2(conv[t[++r]]);
		while (r > q.r) rem(conv[t[r--]]);
		while (l < q.l) rem(conv[t[l++]]);
		while (l > q.l) add2(conv[t[--l]]);
		q.ans = findAns(q.l, q.r);
	}
}

int main() {
	scanf("%d%d", &N, &Q);
	int p = 0;
	FOR(i, N) {
		scanf("%d", &t[i]);
		if (!conv.count(t[i])) conv[t[i]] = p++;
	}
	int l, r;
	M = N + 1;
	FOR(i, Q){
		scanf("%d%d", &l, &r); --l, --r;
		qs.pb({l, r, i, 0});
	}
	SQ = max((int)sqrt(N), 1);
	sort(qs.begin(), qs.end(), sorte);
	mo();
	sort(qs.begin(), qs.end(), sort2);
	
	FOR(i, Q){
		printf("%d\n", qs[i].ans);
	}
}