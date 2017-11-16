#include <bits/stdc++.h>
using namespace std;
#define MAXN 30

bool c[MAXN][MAXN][MAXN];

int main() {
	int N, x;
	int t = 0;
	while(scanf("%d", &N), N) {
		if (t > 0) printf("\n\n");
		t++;
		//clear
		for(int i=0; i<MAXN; i++) {
			for(int j=0; j<MAXN; j++) {
				for(int k=0; k<MAXN; k++) c[i][j][k] = false;
			}
		}
		//read
		for(int i=0; i<N; i++) {
			for(int j=0; true; j++) {
				scanf("%d", &x);
				if (x == 0) break;
				for(int k=0; k<x; k++) c[i][j][k] = true;
			}
		}
		//left
		for(int k=0; k<MAXN; k++) {
			bool h = false;
			for(int i=0; i<MAXN; i++) {
				x = 0;
				for(int j=0; c[i][j][k]; j++) x++;
				if (x == 0) {
					if (h) printf("\n");
					break;
				}
				else {
					if (h) printf(" ");
					h = true;
					printf("%d", x);
				}
			}
		}
		printf("\n");
		//right
		for(int j=0; j<MAXN; j++) {
			bool h = false;
			for(int k=0; k<MAXN; k++) {
				x = 0;
				for(int i=0; c[i][j][k]; i++) x++;
				if (x == 0) {
					if (h) printf("\n");
					break;
				}
				else {
					if (h) printf(" ");
					h = true;
					printf("%d", x);
				}
			}
		}
	}
	return 0;
}