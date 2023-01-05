#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009

char tab[MAXN][MAXN];

void solve(int l, int r, int h) {
	if (r < l) return;
	
	//printf("(%d,%d)\n", l, r);
	
	if (l == r) {
		printf("%s\n", tab[l]+h);
	}
	else {
		int last = l;
		for(int i=l; i<=r; i++) {
			if (tab[i][h] != tab[last][h] || (tab[i][h] != '*' && tab[i][h] != '#')) {
				if (i > last) {
					if (h > 0) printf("<li>\n");
					if (tab[last][h] == '*' && i-1>last) printf("<ul>\n");
					if (tab[last][h] == '#' && i-1>last) printf("<ol>\n");
					solve(last, i-1, h+(i-1>last));
					if (tab[last][h] == '*' && i-1>last) printf("</ul>\n");
					if (tab[last][h] == '#' && i-1>last) printf("</ol>\n");
					if (h > 0) printf("</li>\n");
				}
				last = i;
			}
		}
		if (h > 0) printf("<li>\n");
		if (tab[last][h] == '*' && r>last) printf("<ul>\n");
		if (tab[last][h] == '#' && r>last) printf("<ol>\n");
		solve(last, r, h+(r>last));
		if (tab[last][h] == '*' && r>last) printf("</ul>\n");
		if (tab[last][h] == '#' && r>last) printf("</ol>\n");
		if (h > 0) printf("</li>\n");
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	int N = 0;
	while(!feof(stdin)) {
		scanf(" %s ", tab[N++]);
	}
	solve(0, N-1, 0);
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}