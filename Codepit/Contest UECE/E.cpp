#include <bits/stdc++.h>
using namespace std;

int main() {
	int T, N;
	scanf("%d", &T);
	while(T-->0) {
		scanf("%d", &N);
		if (N > 1 && N <= 3) printf("second\n");
		else printf("first\n");
	}
	return 0;
}