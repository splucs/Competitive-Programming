#include <cstdio>

int main()
{
	int N, bal, x, caseNo=1;
	while(true){
		scanf("%d", &N);
		if (N==0) break;
		bal=0;
		for(int i=0; i<N; i++){
			scanf("%d", &x);
			if (x>0 && x<100) bal++;
			if (x==0) bal--;
		}
		printf("Case %d: %d\n", caseNo++, bal);
	}
	return 0;
}