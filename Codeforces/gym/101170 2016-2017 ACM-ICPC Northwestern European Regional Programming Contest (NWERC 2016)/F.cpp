#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000009
#define FOR(x,n) for (int x = 0; x < n; x++)
typedef pair<int, int> ii;

int dumbels[MAXN][2];
int totals[2*MAXN];
vector<int> un;

bool ordenado(int val, int n) {
	int prv = -1, cnt = 0;
	for (int i = 0; i < n; i++) {
		if (dumbels[i][0] <= val) continue;
		else if (cnt == 1 && prv != dumbels[i][0]) return false;
		else if (cnt == 1 && prv == dumbels[i][0]) {
			cnt = 0;
			prv = -1;
		}
		else if (cnt == 0) {
			cnt = 1;
			prv = dumbels[i][0];
		}
	}
	if (prv != -1) return false;
	for (int i = 0; i < n; i++) {
		if (dumbels[i][1] <= val) continue;
		else if (cnt == 1 && prv != dumbels[i][1]) return false;
		else if (cnt == 1 && prv == dumbels[i][1]) {
			cnt = 0;
			prv = -1;
		}
		else if (cnt == 0) {
			cnt = 1;
			prv = dumbels[i][1];
		}
	}
	if (prv != -1) return false;
	return true;
}

int main() {
	int n;
	scanf("%d", &n);
	FOR(x, n) {
		scanf("%d", &dumbels[x][0]);
		totals[x] = dumbels[x][0];
	}
	FOR(x, n) {
		scanf("%d", &dumbels[x][1]);
		totals[x+n] = dumbels[x][1];
	}
	sort(totals, totals + 2*n);
	if (ordenado(0, n)) { printf("0\n"); return 0; }
	
	un.push_back(0);
	for (int i = 0; i < n; i++) un.push_back(totals[2*i]);
	
	
	int ini = 0, fim = un.size()-1;
	while(ini < fim-1) {
		int mid = (ini + fim)/2;
		if (ordenado(un[mid], n)) {
			fim = mid;
		} else {
			ini = mid;
		}
	}
	printf("%d\n", un[ini+1]);
}