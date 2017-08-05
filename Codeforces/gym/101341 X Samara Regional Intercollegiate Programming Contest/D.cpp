#include <bits/stdc++.h>
using namespace std;

int gcd(int x, int y){
	if (y == 0) return x;
	return gcd(y, x%y);
}

int main() {
	int N, x, v;
	scanf("%d %d", &N, &x);
	int g = 0;
	for(int i=0; i<N; i++) {
		scanf("%d", &v);
		g = gcd(g, v);
	}
	if (x < 0) x = -x;
	if (x % g == 0) printf("YES\n");
	else printf("NO\n");
	return 0;
}