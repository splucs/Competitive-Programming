#include <bits/stdc++.h>
using namespace std;
#define MAXN 19
#define MOD 1000000007LL

typedef long long ll;

int mex[MAXN][MAXN];

int Mex(int N, int B) {
	if (B % 2 != 0) return N%2;
	int s = N % (B + 1);
	if (s == B) return 2;
	return s % 2;
}

int main() {
	freopen("powers.in", "r", stdin);
	
	int T, N, B, K;
	scanf("%d", &T);
	while(T-->0) {
		scanf("%d", &K);
		int ans = 0;
		while(K-->0) {
			scanf("%d %d", &B, &N);
			ans ^= Mex(N, B);
		}
		if (ans) printf("1\n");
		else printf("2\n");
	}
	
	fclose(stdin); 
	return 0;
}