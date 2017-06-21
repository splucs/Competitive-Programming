#include <bits/stdc++.h>
using namespace std;
#define MAXN 30

int id[MAXN], am[MAXN], N, T;

bool comp(int i, int j) {
	return am[i] > am[j];
}

void process(int n) {
	if (n%2 == 0) {
		printf(" %c", id[n] + 'A');
		am[id[n]]--;
		n--;
	}
	while(n >= 0) {
		printf(" %c%c", id[n] + 'A', id[n-1] + 'A');
		am[id[n]]--;
		am[id[n-1]]--;
		n -= 2;
	}
}

int main(){
	scanf("%d", &T);
	for(int caseNo = 1; caseNo <= T; caseNo++) {
		scanf("%d", &N);
		for(int i=0; i<N; i++) {
			id[i] = i;
			scanf("%d", &am[i]);
		}
		sort(id, id+N, &comp);
		printf("Case #%d:", caseNo);
		for(int i=0; i+1<N; i++){
			while (am[id[i]] > am[id[i+1]]) process(i);
		}
		while(am[id[0]] > 0) process(N-1);
		printf("\n");
	}
	return 0;
}