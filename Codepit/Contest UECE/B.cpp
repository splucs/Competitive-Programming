#include <bits/stdc++.h>
using namespace std;

int main() {
	int T, a, b;
	scanf("%d", &T);
	while(T-->0) {
		scanf("%d %d", &a, &b);
		if (a >= b) printf("FunkyMonkeys\n");
		else printf("WeWillEatYou\n");
	}
	return 0;
}