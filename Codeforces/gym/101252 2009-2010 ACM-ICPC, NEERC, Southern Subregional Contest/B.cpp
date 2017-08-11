#include <bits/stdc++.h>
using namespace std;
#define MAXN 10

bool white[MAXN][MAXN];
int value[MAXN][MAXN];
int mright[MAXN][MAXN], mtop[MAXN][MAXN];
int vright[MAXN][MAXN], vtop[MAXN][MAXN];
int lright[MAXN][MAXN], ltop[MAXN][MAXN];
int hright[MAXN][MAXN], htop[MAXN][MAXN];
int N, M;

bool backtrack(const int i, const int j) {
	if (i + j == 0) return true;
	if (!white[i][j]) {
		if(backtrack(i - (j==1?1:0), j == 1 ? M : j-1)) return true;
	}
	else {
		int avail = mright[i][j+1] | mtop[i+1][j];
		for(int k=9; k>=1; k--) {
			if (avail & (1<<k)) continue;
			value[i][j] = k;
			
			vright[i][j] = k + (white[i][j+1] ? vright[i][j+1] : 0);
			if (vright[i][j] < lright[i][j] || vright[i][j] > hright[i][j]) continue;
			
			vtop[i][j] = k + (white[i+1][j] ? vtop[i+1][j] : 0);
			if (vtop[i][j] < ltop[i][j] || vtop[i][j] > htop[i][j]) continue;
			
			mright[i][j] = (1<<k) | (white[i][j+1] ? mright[i][j+1] : 0);
			mtop[i][j] = (1<<k) | (white[i+1][j] ? mtop[i+1][j] : 0);
			if(backtrack(i - (j==1?1:0), j == 1 ? M : j-1)) return true;
		}
	}
	return false;
}

void boundsright(int i, int j, int v) {
	int hi = v;
	int lo = v;
	for(int c=1; white[i][j]; j++, c++) {
		hright[i][j] = hi;
		lright[i][j] = lo;
		hi -= c;
		lo -= 10-c;
	}
}

void boundstop(int i, int j, int v) {
	int hi = v;
	int lo = v;
	for(int c=1; white[i][j]; i++, c++) {
		htop[i][j] = hi;
		ltop[i][j] = lo;
		hi -= c;
		lo -= 10-c;
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	memset(&vright, 0, sizeof vright);
	memset(&vtop, 0, sizeof vtop);
	memset(&mright, 0, sizeof mright);
	memset(&mtop, 0, sizeof mtop);
	memset(&hright, 0, sizeof hright);
	memset(&htop, 0, sizeof htop);
	memset(&lright, 0, sizeof lright);
	memset(&ltop, 0, sizeof ltop);
	memset(&white, false, sizeof white);
	scanf("%d %d", &N, &M);
	char buffer[MAXN];
	for(int i=1; i<=N; i++) {
		for(int j=1; j<=M; j++) {
			scanf(" %s ", buffer);
			if (buffer[0] == '.') {
				white[i][j] = true;
			}
			if (buffer[0] == 'X' && buffer[3] == 'X') {
				vtop[i][j] = -1;
				vright[i][j] = -1;
			}
			else if (buffer[0] == 'X') {
				sscanf(buffer, "XX\\%d", &vright[i][j]);
				vtop[i][j] = -1;
			}
			else if (buffer[3] == 'X') {
				sscanf(buffer, "%d\\XX", &vtop[i][j]);
				vright[i][j] = -1;
			}
			else {
				sscanf(buffer, "%d\\%d", &vtop[i][j], &vright[i][j]);
			}
		}
	}
	for(int i=1; i<=N; i++) {
		for(int j=1, v1, v2; j<=M; j++) {
			if (!white[i][j] && vtop[i][j] >= 0) boundstop(i+1, j, vtop[i][j]);
			if (!white[i][j] && vright[i][j] >= 0) boundsright(i, j+1, vright[i][j]);
		}
	}
	if(!backtrack(N, M)) {
		printf("error!\n");
	}
	for(int i=1; i<=N; i++) {
		for(int j=1; j<=M; j++) {
			if (white[i][j]) printf("%d ", value[i][j]);
			else printf("_ ");
		}
		printf("\n");
	}
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}