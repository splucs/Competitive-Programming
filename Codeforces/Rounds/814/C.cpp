#include<bits/stdc++.h>
using namespace std;
#define MAXN 1509
#define ALFA 'z' - 'a'
#define state dp[i][m][c]

int dp[MAXN][MAXN][ALFA+1], n, q, ans[MAXN][ALFA+1];
char s[MAXN];

int main() {
	scanf("%d %s %d", &n, s+1, &q);
	for(int i=0; i<=n; i++){
		for(int m=0; m<=n; m++){
			for(int c=0; c<=ALFA; c++){
				if (i == 0){
					state = 0;
				}
				else if (m == 0){
					if ((s[i]-'a') == c) state = 1 + dp[i-1][m][c];
					else state = 0;
				}
				else{
					if ((s[i]-'a') == c) state = 1 + dp[i-1][m][c];
					else state = 1 + dp[i-1][m-1][c];
				}
			}
		}
	}
	for(int m=0; m<=n; m++){
		for(int c=0; c<=ALFA; c++){
			ans[m][c] = 0;
			for(int i=1; i<=n; i++){
				ans[m][c] = max(ans[m][c], dp[i][m][c]);
			}
		}
	}
	int m;
	char c;
	while(q-->0){
		scanf("%d %c", &m, &c);
		printf("%d\n", ans[m][c-'a']);
	}
	return 0;
}