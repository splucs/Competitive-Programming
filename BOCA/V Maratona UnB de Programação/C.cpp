#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009

int p[MAXN], q[MAXN];

int main() {
	int N, K;
	while(scanf("%d %d", &N, &K) != EOF) {
		
		char c;
		for(int i=0; i<N; i++) {
			scanf(" %c", &c);
			p[i] = c - '0';
		}
		for(int i=0; i<N; i++) {
			scanf(" %c", &c);
			q[i] = c - '0';
		}
		
		int dist = 0;
		for(int i=0; i<N; i++) {
			if (p[i] == q[i]) continue;
			else if (abs(p[i] - q[i]) == 1) dist++;
			else if (q[i] == 0 && p[i] == 9) dist++;
			else if (p[i] == 0 && q[i] == 9) dist++;
			else dist += K+1;
		}
		
		if (dist <= K) printf("Acesso garantido\n");
		else printf("Acesso negado\n");
	}
	
	return 0;
}