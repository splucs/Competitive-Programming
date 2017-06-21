#include <bits/stdc++.h>
using namespace std;
#define MAXN 2509

int appeared[MAXN];

int main(){
	int T, n, x;
	scanf("%d", &T);
	for(int caseNo = 1; caseNo<=T; caseNo++){
		memset(&appeared, 0, sizeof appeared);
		scanf("%d", &n);
		for(int i=0; i<(2*n-1)*n; i++){
			scanf("%d", &x);
			appeared[x]++;
		}
		printf("Case #%d:", caseNo);
		for(int i=0; i<MAXN; i++){
			if (appeared[i] % 2 != 0) printf(" %d", i);
		}
		printf("\n");
	}
	return 0;
}