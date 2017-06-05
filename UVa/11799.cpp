#include <cstdio>

int main()
{
	int T, N, x, max;
	scanf("%d", &T);
	for(int caseNo=1; caseNo<=T; caseNo++){
		max=-1;
		scanf("%d", &N);
		for(int i=0; i<N; i++){
			scanf("%d", &x);
			if (x>max) max=x;
		}
		printf("Case %d: %d\n", caseNo, max);
	}
	return 0;
}