#include <bits/stdc++.h>
using namespace std;
#define FOR1(i, n) for(int i = 1; i <= n; i++)


int main() {
	int T;
	scanf("%d", &T);
	FOR1(caseNo, T) {
		int n;
		scanf("%d", &n);
		printf("%d\n", (1<<n)-1);
	}
	return 0;
}