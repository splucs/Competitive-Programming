#include <bits/stdc++.h>
using namespace std;

int gcd(int x, int y) {
	if (y == 0) return x;
	return gcd(y, x%y);
}

int main() {
	int x, y, z, T;
	scanf("%d", &T);
	while(T --> 0) {
		scanf("%d %d %d", &x, &y, &z);
		bool ok = true;
		if (gcd(x, gcd(y, z)) != 1) ok = false;
		if (x*x != y*y + z*z && y*y != x*x + z*z && z*z != y*y + x*x) ok = false;
		if (ok) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}