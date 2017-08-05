#include <bits/stdc++.h>
using namespace std;
#define state dp[a][b][c]

int N, D, C;
double dp[11][11][11], pas[51][51];

double Pas(int n, int k) {
	if (pas[n][k] > -0.5) return pas[n][k];
	if (n == k || k == 0) return pas[n][k] = 1.0;
	else return pas[n][k] = Pas(n-1, k) + Pas(n-1, k-1);
}

double prob(int aa, int ab, int ac, int a, int b, int c) {
	return Pas(a, aa)*Pas(b, ab)*Pas(c, ac)*Pas(N-a-b-c, D-aa-ab-ac)/Pas(N, D);
}

double DP(const int a, const int b, const int c) {
	if (state > -0.5) return state;
	if (c == 0 && (a == 0 || b == 0)) return state = 0.0;
	state = 1.0;
	for(int aa=0; aa<=a; aa++) {
		for(int ab=0; ab<=b; ab++) {
			for(int ac=0; ac<=c; ac++) {
				if (aa+ab+ac == 0) continue;
				state += prob(aa, ab, ac, a, b, c)*DP(a-aa, b-ab, c-ac);
			}
		}
	}
	state /= 1.0-prob(0, 0, 0, a, b, c);
	//printf("dp[%d][%d][%d] = %f\n", a, b, c, state);
	return state;
}

int main(){
	scanf("%d %d %d", &N, &D, &C);
	set<int> b1;
	int a = 0, b = 0, c = 0, x;
	for(int i=0; i<C; i++) {
		scanf("%d", &x);
		b1.insert(x);
		a++;
	}
	for(int i=0; i<C; i++) {
		scanf("%d", &x);
		if (b1.count(x)){
			a--;
			c++;
		}
		else b++;
	}
	for(int i=0; i<=a; i++) {
		for(int j=0; j<=b; j++) {
			for(int k=0; k<=c; k++) {
				dp[i][j][k] = -1.0;
			}
		}
	}
	for(int i=0; i<=N; i++) {
		for(int j=0; j<=N; j++){
			pas[i][j] = -1.0;
		}
	}
	printf("%.5f\n", DP(a, b, c));
	return 0;
}