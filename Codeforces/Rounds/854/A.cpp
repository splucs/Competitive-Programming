#include <bits/stdc++.h>
using namespace std;

int gcd(int x, int y) {
	if (y == 0) return x;
	return gcd(y, x%y);
}

int main() {
	int n;
	scanf("%d", &n);
	int a = -1000, b = 1000;
	for(int i=1; i<n; i++) {
		int j = n-i;
		if (i > j) continue;
		if (gcd(i, j) != 1) continue;
		if (j-i < b-a) {
			b = j;
			a = i;
		}
	}
	printf("%d %d\n", a, b);
	return 0;
}