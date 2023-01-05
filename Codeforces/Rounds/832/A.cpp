#include <bits/stdc++.h>
using namespace std;

int main() {
	long long N, K;
	scanf("%I64d %I64d", &N, &K);
	N /= K;
	if (N % 2 == 0) printf("NO\n");
	else printf("YES\n");
	return 0;
}