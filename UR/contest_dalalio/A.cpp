#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009
#define ALFA 256

char str[MAXN], ans[MAXN];
int nxt[MAXN][ALFA], n;

void backtrack(const int i, const int j){
	ans[j+1] = 0;
	for(ans[j] = 'a'; ans[j] <= 'z'; ans[j]++) {
		if (nxt[i][ans[j]] < 0) continue;
		printf("%s\n", ans);
		backtrack(nxt[i][ans[j]]+1, j+1);
	}
	ans[j] = 0;
}

int main() {
	while(scanf(" %s", str) != EOF) {
		n = strlen(str);
		for(char c='a'; c<='z'; c++) nxt[n][c] = -1;
		for(int i = n-1; i>=0; i--) {
			for(char c='a'; c<='z'; c++){
				nxt[i][c] = nxt[i+1][c];
			}				
			nxt[i][str[i]] = i;
		}
		ans[0] = 0;
		backtrack(0, 0);
		printf("\n");
	}
	return 0;
}