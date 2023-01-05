#include <bits/stdc++.h>
using namespace std;
#define MAXN 59
#define MAXM 320
#define MOD 1000000007
#define INF 1000000009
#define EPS 1e-7
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define pb push_back
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;

char mat[MAXN][MAXN];
int N, M;

bool check(int i) {
	bool ok = true;
	FOR(it, N) {
		bool checkthis = false;
		FOR(jt, M) {
			if (mat[i][jt] == '#' && mat[it][jt] == '#') checkthis = true;
		}
		if (!checkthis) continue;
		if (strcmp(mat[i], mat[it]) != 0) ok = false;
	}
	return ok;
}

int main() {
	scanf("%d %d", &N, &M);
	FOR(i, N) scanf(" %s", mat[i]);
	bool ok = true;
	FOR(i, N) {
		if (!check(i)) ok = false;
	}
	if (ok) printf("Yes\n");
	else printf("No\n");
	return 0;
}