#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, k;
	scanf("%d %d", &n, &k);
	if (n == k || k == 0) printf("0 ");
	else printf("1 ");
	printf("%d\n", min(2*k, n-k));
	return 0;
}