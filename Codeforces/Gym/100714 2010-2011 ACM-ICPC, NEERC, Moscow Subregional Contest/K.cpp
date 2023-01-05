#include <bits/stdc++.h>
using namespace std;
#define MAXN 209

int xb, xt, yb, yt, N, M;
bool tried[MAXN][MAXN];
char str[MAXN];

int main(){
	scanf("%d %d", &N, &M);
	xb = yb = 1;
	xt = M; yt = N;
	memset(&tried, false, sizeof tried);
	int ci=1, cj=1, ofx=0, ofy=0;
	char op;
	while(true) {
		while (tried[ci][cj]) {
			cj++;
			if (cj > M) cj=1, ci++;
		}
		printf("%d %d\n", ci+ofy, cj+ofx);
		tried[ci][cj] = true;
		fflush(stdout);
		scanf(" %s", str);
		if (0 == strcmp(str, "DETECTED")) return 0;
		else op = str[0];
		if (op == 'L') {
			xb++; xt++;
			ofx--;
			for(int i=1; i<=N && xb-1>=1; i++) tried[i][xb-1] = true;
		}
		if (op == 'R') {
			xb--; xt--;
			ofx++;
			for(int i=1; i<=N && xt+1<=M; i++) tried[i][xt+1] = true;
		}
		if (op == 'U') {
			yb++; yt++;
			ofy--;
			for(int j=1; j<=M && yb-1>=1; j++) tried[yb-1][j] = true;
		}
		if (op == 'D') {
			yb--; yt--;
			ofy++;
			for(int j=1; j<=M && yt+1<=N; j++) tried[yt+1][j] = true;
		}
	}
	return 0;
}