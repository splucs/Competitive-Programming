#include <bits/stdc++.h>
using namespace std;
#define MAXN 109
#define MOD 1000000007
#define INF 1000000009
#define EPS 1e-7
#define FOR(x,n) for(int x=0; x<n; x++)
#define FOR1(x,n) for(int x=1; x<=n; x++)
#define pb push_back
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;

int R, C, H, V;
int rowsum[MAXN], tot, perPart;
char field[MAXN][MAXN];
int belong[MAXN];

bool simulateCut(int col, int ncuts) {
	memset(&rowsum, 0, sizeof rowsum);
	FOR(i, R) FOR(j, col) {
		if (field[i][j] == '@') rowsum[belong[i]]++;
	}
	FOR(i, H) {
		if (rowsum[i] != perPart*ncuts) return false;
	}
	return true;
}

int main() {
	int T;
	scanf("%d", &T);
	FOR1(caseNo, T) {
		scanf("%d %d %d %d", &R, &C, &H, &V);
		H++; V++;
		tot = 0;
		bool ok = true;
		FOR(i, R) {
			scanf(" %s", &field[i]);
			FOR(j, C) {
				if (field[i][j] == '@') tot++;
			}
			rowsum[i] = tot;
		}
		if (tot % (H*V) != 0) ok = false;
		perPart = tot/(H*V);
		bool app[MAXN*MAXN];
		memset(&app, false, sizeof app);
		FOR(i, R) {
			app[rowsum[i]] = true;
		}
		FOR1(s, H) {
			if (!app[s*(tot/H)]) {
				ok = false;
			}
		}
		int id = 0, limit = tot/H;
		FOR(i, R) {
			while(rowsum[i] > limit) {
				id++;
				limit += tot/H;
			}
			belong[i] = id;
		}
		int col = 1;
		FOR1(ncuts, V) {
			bool found = false;
			for(; col <= C; col++) {
				if (simulateCut(col, ncuts)) {
					found = true;
					break;
				}
			}
			if (!found) {
				ok = false;
				break;
			}
		}
		if (ok) printf("Case #%d: POSSIBLE\n", caseNo);
		else printf("Case #%d: IMPOSSIBLE\n", caseNo);
	}
	return 0;
}