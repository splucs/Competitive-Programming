#include <bits/stdc++.h>
using namespace std;
#define MAXN 300009
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
#define DIG 30

int sz[MAXM], l[MAXM], r[MAXM], cnt = 0;

int newnode() {
	l[cnt] = r[cnt] = -1;
	sz[cnt] = 0;
	cnt++;
	return cnt-1;
}

int root;

void insert(int N) {
	int u = root;
	sz[u]++;
	for(int i = DIG-1; i >= 0; i--) {
		if (N & (1<<i)) {
			if (r[u] == -1) r[u] = newnode();
			u = r[u];
		}
		else {
			if (l[u] == -1) l[u] = newnode();
			u = l[u];
		}
		sz[u]++;
	}
}

int ans;
bool search(int u, int h, int num, int N) {
	if (u == -1 || sz[u] <= 0) return false;
	sz[u]--;
	if (h == -1) {
		ans = num;
		return true;
	}
	if (N & (1<<h)) {
		return search(r[u], h-1, num, N) || search(l[u], h-1, num | (1<<h), N);
	}
	else {
		return search(l[u], h-1, num, N) || search(r[u], h-1, num | (1<<h), N);
	}
}

int A[MAXN], P[MAXN], N;

int main() {
	root = newnode();
	scanf("%d", &N);
	FOR(i, N) scanf("%d", &A[i]);
	FOR(i, N) {
		scanf("%d", &P[i]);
		insert(P[i]);
	}
	FOR(i, N) {
		search(root, DIG-1, 0, A[i]);
		printf("%d ", ans);
	}
	printf("\n");
	return 0;
}