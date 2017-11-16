#include <bits/stdc++.h>
using namespace std;
#define MAXN 109
#define INF (1<<30)

char s1[MAXN], s2[MAXN];
int a[MAXN], b[MAXN];
int N, ans, aux, dp[MAXN][MAXN][4][2], A[MAXN][MAXN][4][2];
typedef pair<int, pair<int, int> > iii;
vector<iii> tr;

void printans(int i, int j, int k, int t) {
	if (t == 1) {
		//printf("printans %d %d %d %d -> %d\n", i, j, k, t, A[i][j][k][1]);
		//if (A[i][j][k][1] != 0) printf("%d %d %d\n", i+1, j+1, A[i][j][k][1]);
		if (A[i][j][k][1] > 0) tr.push_back(iii(i+1, make_pair(j+1, A[i][j][k][1])));
		printans(i, j, (k+A[i][j][k][1])%4, 0);
	}
	else {
		if (i < j) {
			printans(i, A[i][j][k][0]-1, k, 1);
			printans(A[i][j][k][0], j, k, 1);
		}
	}
}

int main() {
	freopen("transform.in", "r", stdin);
	freopen("transform.out", "w", stdout);
	
	scanf(" %s %s", s1, s2);
	N = strlen(s1);
	for(int i=0; i<N; i++) {
		if (s1[i] == 'A') 		a[i] = 0;
		else if (s1[i] == 'C') 	a[i] = 1;
		else if (s1[i] == 'G') 	a[i] = 2;
		else if (s1[i] == 'T') 	a[i] = 3;
		//printf("%d", a[i]);
	}
	//printf("\n");
		
	for(int i=0; i<N; i++) {
		if (s2[i] == 'A') 		b[i] = 0;
		else if (s2[i] == 'C') 	b[i] = 1;
		else if (s2[i] == 'G') 	b[i] = 2;
		else if (s2[i] == 'T') 	b[i] = 3;
		//printf("%d", b[i]);
	}
	//printf("\n");
	
	for(int s=0; s<N; s++) {
		for(int i=0; i+s<N; i++) {
			int j = s+i;
			
			//type 0
			for(int k=0; k<4; k++) {
				ans = INF;
				if (s == 0) {
					if ((a[i] + k) % 4 == b[i] % 4) ans = 0;
					else ans = INF;
				}
				else for(int it=i+1; it<=j; it++) {
					if (ans > dp[i][it-1][k][1] + dp[it][j][k][1]) {
						ans = dp[i][it-1][k][1] + dp[it][j][k][1];
						A[i][j][k][0] = it;
					}
				}
				dp[i][j][k][0] = ans;
				//printf("dp[%d][%d][%d][0] = %d\n", i, j, k, ans);
			}
			
			//type 1
			for(int k=0; k<4; k++) {
				ans = INF;
				A[i][j][k][1] = -1;
				for(int kt=0; kt<4; kt++) {
					if (ans > dp[i][j][(k+kt)%4][0] + (kt!=0 ? 1 : 0)) {
						ans = dp[i][j][(k+kt)%4][0] + (kt!=0 ? 1 : 0);
						A[i][j][k][1] = kt;
					}
				}
				dp[i][j][k][1] = ans;
				//printf("dp[%d][%d][%d][1] = %d\n", i, j, k, ans);
			}
		}
	}
	printf("%d\n", dp[0][N-1][0][1]);
	printans(0, N-1, 0, 1);
	sort(tr.begin(), tr.end());
	for(int i=0; i<(int)tr.size(); i++) {
		printf("%d %d %d\n", tr[i].first, tr[i].second.first, tr[i].second.second);
	}
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}