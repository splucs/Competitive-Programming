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
#define EPS 1e-9

int a[MAXN], b[MAXN], n, k1, k2;

struct cmp {
	bool operator ()(int i, int j) {
		return abs(a[i]-b[i]) < abs(a[j]-b[j]);
	}
};

priority_queue<int, vector<int>, cmp> pq;

int main() {
	scanf("%d %d %d", &n, &k1, &k2);
	FOR(i, n) scanf("%d", &a[i]);
	FOR(i, n) scanf("%d", &b[i]);
	FOR(i, n) pq.push(i);
	while(k1--) {
		int i = pq.top();
		pq.pop();
		if (a[i] > b[i]) a[i]--;
		else a[i]++;
		pq.push(i);
	}
	while(k2--) {
		int i = pq.top();
		pq.pop();
		if (a[i] > b[i]) b[i]++;
		else b[i]--;
		pq.push(i);
	}
	ll E = 0;
	FOR(i, n) {
		E += (a[i]-b[i])*1ll*(a[i]-b[i]);
	}
	printf("%I64d\n", E);
	return 0;
}