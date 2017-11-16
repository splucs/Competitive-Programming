#include <bits/stdc++.h>
using namespace std;
#define MAXN 50
#define state dp[i][h1][h2][h3][h4]

char dp[10][MAXN][MAXN][MAXN][MAXN];
int arr[20];
int d1[8] = {4, 1, 2, 1, 1, 2, 3, 1};
int d2[8] = {0, 1, 2, 2, 3, 1, 1, 1};
int d3[8] = {0, 1, 0, 1, 0, 1, 0, 2};
int d4[8] = {0, 1, 0, 0, 0, 0, 0, 0};

bool computeDp(const int h) {
	for(int i=9; i>=0; i--)
		for(int h1 = h; h1>=0; h1--) 
			for(int h2 = h; h2>=0; h2--) 
				for(int h3 = h; h3>=0; h3--) 
					for(int h4 = h; h4>=0; h4--) {
						state = -1;
						
						if (h1 > h) continue;
						else if (h1 == h) {
							if (i < 9) state = dp[i+1][h2][h3][h4][arr[i+4]];
							else state = 0;
						}
						else {
							for(int k=0; k<8; k++) {
								if (i >= 9 && d2[k] > 0) continue;
								if (i >= 8 && d3[k] > 0) continue;
								if (i >= 7 && d4[k] > 0) continue;
								if (h1+d1[k] <= h && h2+d2[k] <= h && h3+d3[k] <= h && h4+d4[k] <= h &&
								dp[i][h1+d1[k]][h2+d2[k]][h3+d3[k]][h4+d4[k]] != -1) {
									state = 'A' + k;
									break;
								}
							}
						}
						
						//printf("(%d) dp[%d][%d][%d][%d][%d] = %d\n", h, i, h1, h2, h3, h4, state);
					}
	return dp[0][arr[0]][arr[1]][arr[2]][arr[3]] != -1;
}

int main() {
	
	int sum = 0, mx = 0;
	for(int i=0; i<10; i++) {
		scanf("%d", &arr[i]);
		sum += arr[i];
		mx = max(mx, arr[i]);
	}
	
	int h;
	for(h = mx; h<MAXN; h++) {
		if ((h*10 - sum) % 4 != 0) continue;
		if (computeDp(h)) break;
	}
	
	int i = 0, h1 = arr[0], h2 = arr[1], h3 = arr[2], h4 = arr[3];
	vector<int> ansi;
	string ansc;
		
	while(state != 0) {
		while (h1 == h) {
			h1 = h2;
			h2 = h3;
			h3 = h4;
			h4 = arr[i+4];
			i++;
		}
		ansc.push_back(state);
		ansi.push_back(i+1);
		int k = state - 'A';
		h1 += d1[k];
		h2 += d2[k];
		h3 += d3[k];
		h4 += d4[k];
	}
	
	printf("%u\n", ansi.size());
	for(i=0; i<(int)ansi.size(); i++) {
		printf("%c %d\n", ansc[i], ansi[i]);
	}
	
	return 0;
}