#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009
#define INF (1<<30)

int dpmax[MAXN][MAXN], dpmin[MAXN][MAXN], N, sum[MAXN];
char str[MAXN];

int main() {
	while(scanf(" %s", str) != EOF) {
		
		N = strlen(str);
		
		for(int i=0; i<MAXN; i++) {
			
			if (str[i] > '9' || str[i] < '0') sum[i] = 1;
			else sum[i] = 0;
			if (i > 0) sum[i] += sum[i-1];
			
			for(int j=0; j<MAXN; j++) {
				dpmax[i][j] = -INF;
				dpmin[i][j] = INF;
			}
		}
		
		for(int s=0; s<N; s++) {
			for(int i=0, j; i+s<N; i++) {
				j = i+s;
				
				if (str[i] == '+') {
					for(int k=i+1; k<j; k++) {
						if (dpmax[i][j] < dpmax[i+1][k] + dpmax[k+1][j])
							dpmax[i][j] = dpmax[i+1][k] + dpmax[k+1][j];
						if (dpmin[i][j] > dpmin[i+1][k] + dpmin[k+1][j])
							dpmin[i][j] = dpmin[i+1][k] + dpmin[k+1][j];
					}
				}
				else if (str[i] == '-') {
					dpmin[i][j] = -dpmax[i+1][j];
					dpmax[i][j] = -dpmin[i+1][j];
					for(int k=i+1; k<j; k++) {
						if (dpmax[i][j] < dpmax[i+1][k] - dpmin[k+1][j])
							dpmax[i][j] = dpmax[i+1][k] - dpmin[k+1][j];
						if (dpmin[i][j] > dpmin[i+1][k] - dpmax[k+1][j])
							dpmin[i][j] = dpmin[i+1][k] - dpmax[k+1][j];
					}
				}
				else {
					if (j-i+1<=9 && sum[j] - (i > 0 ? sum[i-1] : 0) == 0 && (str[i] != '0' || i==j)) {
						char aux = 0;
						swap(str[j+1], aux);
						dpmax[i][j] = dpmin[i][j] = atoi(&str[i]);
						swap(str[j+1], aux);
					}
				}
				
				printf("dpmin[%d][%d] = %d, dpmax[%d][%d] = %d\n", i, j, dpmin[i][j], i, j, dpmax[i][j]);
			}
		}
		
		printf("%d %d\n", dpmin[0][N-1], dpmax[0][N-1]);
	}
	
	return 0;
}