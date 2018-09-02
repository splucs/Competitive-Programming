#include <bits/stdc++.h>
#define mod 1000000007
using namespace std;

int c[10009];

int main() {
	c[0] = 1;
	for (int i = 1; i <= 10000; i++) {
		for (int j = i; j <= 10000; j++) {
			c[j] += c[j-i];
			c[j] %= mod;
		}
	}
	int n;
	while (scanf("%d", &n) != EOF) {
		printf("%d\n", c[n]);
	}
}