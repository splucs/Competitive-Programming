#include <bits/stdc++.h>
using namespace std;

int mex(int N, int B) {
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
			ans ^= mex(N, B);
		}
		if (ans) printf("1\n");
		else printf("2\n");
	}
	
	fclose(stdin); 
	return 0;
}