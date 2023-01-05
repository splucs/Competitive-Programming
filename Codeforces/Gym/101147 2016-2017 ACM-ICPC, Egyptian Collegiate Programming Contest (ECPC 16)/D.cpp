#include <bits/stdc++.h>
using namespace std;

long long pascal[30][30];

int main() {
	freopen("popcorn.in", "r", stdin);
	
	for(int n=0; n<30; n++) {
		for(int k=0; k<30; k++) {
			if (k > n) pascal[n][k] = 0;
			else if (k == 0 || k == n) pascal[n][k] = 1;
			else pascal[n][k] = pascal[n-1][k] + pascal[n-1][k-1];
		}
	}
	int T, n, m;
	scanf("%d", &T);
	while(T-->0) {
		scanf("%d %d", &n, &m);
		printf("%I64d\n", pascal[n][m]);
	}
	
	fclose(stdin); 
	return 0;
}