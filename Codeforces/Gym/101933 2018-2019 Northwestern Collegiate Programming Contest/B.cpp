#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)


int main() {
	int n;
	char cmd[10];
	while(scanf("%d", &n) != EOF) {
		bool ok = true;
		FOR1(i, n) {
			scanf(" %s", cmd);
			if (cmd[0] != 'm') {
				int j;
				sscanf(cmd, "%d", &j);
				if (i != j) ok = false;
			}
		}
		if (ok) printf("makes sense\n");
		else printf("something is fishy\n");
	}
	return 0;
}