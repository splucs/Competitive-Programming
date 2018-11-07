#include <bits/stdc++.h>
#define MAXN 10009
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define fi first
#define se second
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
using namespace std;
typedef long long int ll;
typedef pair<int, int> ii;
typedef vector<int> vi;

double a[MAXN], s[MAXN], v[MAXN], x[MAXN];
int id[MAXN];

bool comp(int i, int j) {
	return a[i] > a[j];
}

int main() {
	int n;
	scanf("%d", &n);
	FOR(i, n) {
		scanf("%lf %lf", &a[i], &s[i]);
		id[i] = i;
	}
	sort(id, id+n, comp);
	v[0] = x[0] = 0;
	FOR1(i, n) {
		int ai = a[id[i-1]];
		int si = s[id[i-1]];
		x[i] = x[i-1] + v[i-1]*si + ai*si*si/2;
		v[i] = v[i-1] + ai*si;
	}
	double opt = x[n];
	FOR1(i, n) {
		int ai = a[i-1];
		int si = s[i-1];
		x[i] = x[i-1] + v[i-1]*si + ai*si*si/2;
		v[i] = v[i-1] + ai*si;
	}
	double def = x[n];
	printf("%.1f\n", opt-def);
	return 0;
}