#include <bits/stdc++.h>
using namespace std;

int main() {
	int pos = 0, neg = 0, N, x, y;
	scanf("%d", &N);
	for(int i=0; i<N; i++) {
		scanf("%d %d", &x, &y);
		if (x < 0) neg++;
		else pos++;
	}
	if (neg <= 1 || pos <= 1) printf("Yes\n");
	else printf("No\n");
	return 0;
}