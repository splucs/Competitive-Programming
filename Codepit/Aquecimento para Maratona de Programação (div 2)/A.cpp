#include <bits/stdc++.h>
using namespace std;

int main() {
	int N;
	while(scanf("%d", &N) != EOF) {
		int cnt = 0, v;
		for(int i=0; i<N; i++) {
			scanf("%d", &v);
			cnt += v;
		}
		if (3*cnt >= 2*N) printf("impeachment\n");
		else printf("acusacao arquivada\n");
	}
	return 0;
}