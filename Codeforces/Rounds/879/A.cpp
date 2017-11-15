#include <bits/stdc++.h>
using namespace std;

int N;

int main() {
	scanf("%d", &N);
	int cur = 0, s, d;
	for(int i=0; i<N; i++) {
		scanf("%d %d", &s, &d);
		while(s <= cur) s += d;
		cur = s;
	}
	printf("%d\n", cur);
	return 0;
}