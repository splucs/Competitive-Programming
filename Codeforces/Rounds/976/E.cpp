#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
#define MAXM ((1e+18) + 100)
#define MOD 1000000007
#define INF 1000000009
#define EPS 1e-9
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define pb push_back
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;

int n, id[MAXN];
ll a, b, hp[MAXN], dmg[MAXN];

bool comp(int i, int j) {
	return hp[i]-dmg[i] > hp[j]-dmg[j];
}

int main() {
	scanf("%d %I64d %I64d", &n, &a, &b);
	FOR(i, n) {
		scanf("%I64d %I64d", &hp[i], &dmg[i]);
		id[i] = i;
	}
	sort(id, id+n, comp);
	ll ini = 0;
	ll inc = 0;
	ll mul = 1;
	FOR(i, a) mul *= 2;
	FOR(it, n) {
		int i = id[it];
		if (dmg[i] < hp[i] && it < b) {
			ini += hp[i];
		}
		else ini += dmg[i];
		if (it == b-1) {
			inc = hp[i] - dmg[i];
			if (inc < 0) inc = 0;
		}
	}
	ll ans = ini;
	if (b > 0) {
		FOR(it, n) {
			int i = id[it];
			if (it < b) {
				ll cur = ini;
				if (dmg[i] < hp[i]) cur -= hp[i];
				else cur -= dmg[i];
				hp[i] *= mul;
				if (dmg[i] < hp[i]) cur += hp[i];
				else cur += dmg[i];
				ans = max(ans, cur);
				hp[i] /= mul;
			}
			else {
				ll cur = ini - inc;
				cur -= dmg[i];
				hp[i] *= mul;
				if (dmg[i] < hp[i]) cur += hp[i];
				else cur += dmg[i];
				ans = max(ans, cur);
				hp[i] /= mul;
			}
		}
	}
	printf("%I64d\n", ans);
	return 0;
}