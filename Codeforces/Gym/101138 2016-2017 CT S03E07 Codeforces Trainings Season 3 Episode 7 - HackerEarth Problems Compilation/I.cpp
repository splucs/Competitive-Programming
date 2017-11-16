#include <bits/stdc++.h>
using namespace std;
#define THRESHOLD 90000000000000000LL

typedef long long int ll;

template<typename T>
T modExp(T a, T b, T m) {
    if (b == 0) return 1;
    T c = modExp(a, b / 2, m);
    c = (c * c) % m;
    if (b % 2 != 0) c *= a;
    return c;
}

bool mrtest (ll a, ll s, ll d, ll n){
    ll x = modExp(a, d, n);
    if (x == 1 | x == n-1) return true;
    for (; s > 0 ;s--)
        if ((x = (x * x) % n) == n-1) return true;
    return false;
}

bool isPrimeFast(ll n){
    if (n < 0) n = -n;
    if (n < 5 || n % 2 == 0 || n % 3 == 0)
        return (n == 2 || n == 3);
    ll maxP = sqrt(n) + 2;
    for (ll p = 5; p < maxP; p += 6) {
        if (p < n && n % p == 0) return false;
        if (p+2 < n && n % (p+2) == 0) return false;
	}
    return true;
}

bool millerrabin(ll n){
	if (n < THRESHOLD) return isPrimeFast(n);
	ll s, d;
    if (n % 2 == 0 || n % 3 == 0)
        return (n == 2 || n == 3);
	for (s = 0, d = n-1; d % 2 == 0; s++, d /= 2);
	return  mrtest(2, s, d, n) &&
		(n <= 7 || mrtest (7, s, d, n)) &&
		(n <= 61 || mrtest (61, s, d, n));
}

map<ll, int> v2id;
ll id2v[10];
vector<ll> cand;
int dist[10], rep[10], par[10], cnt;
		
int main() {
	ll a, b;
	while(scanf("%I64d %I64d", &a, &b) != EOF) {
		cnt = 0;
		cand.clear();
		cand.push_back(a-2);
		cand.push_back(a);
		cand.push_back(a+2);
		cand.push_back(2);
		cand.push_back(b-2);
		cand.push_back(b);
		cand.push_back(b+2);
		v2id.clear();
		for(int i=0; i<(int)cand.size(); i++) {
			ll p = cand[i];
			if (!v2id.count(p) && millerrabin(p)) {
				v2id[p] = cnt;
				id2v[cnt] = p;
				dist[cnt] = 20;
				rep[cnt] = 0;
				par[cnt] = -1;
				//printf("map %I64d -> %d\n", p, cnt);
				cnt++;
			}
		}
		queue<int> q;
		int id = v2id[b];
		q.push(id);
		dist[id] = 0;
		rep[id] = 1;
		while(!q.empty()) {
			int i = q.front();
			q.pop();
			//printf("dist[%I64d]=%d ", id2v[i], dist[i]);
			for(int j=0; j<cnt; j++) {
				if (!millerrabin(abs(id2v[i] - id2v[j]))) continue;
				//printf("edge(%I64d,%I64d)\n", id2v[i], id2v[j]);
				if (dist[j] > dist[i] + 1) {
					dist[j] = dist[i] + 1;
					par[j] = i;
					rep[j] = 0;
					q.push(j);
				}
				if (dist[j] == dist[i] + 1) {
					rep[j] += rep[i];
				}
			}
		}
		id = v2id[a];
		if (par[id] == -1) printf("Unlucky Benny\n");
		else if (rep[id] > 1) printf("Poor Benny\n");
		else {
			while(id != -1) {
				printf("%I64d", id2v[id]);
				id = par[id];
				if (id != -1) printf("->");
			}
			printf("\n");
		}
	}
	return 0;
}