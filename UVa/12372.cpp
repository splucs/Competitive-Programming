#include <cstdio>

int main()
{
	int N, x;
	bool good;
	scanf("%d", &N);
	for(int caseNo = 1; caseNo<=N; caseNo++){
		good = true;
		scanf("%d", &x);
		if (x>20) good=false;
		scanf("%d", &x);
		if (x>20) good=false;
		scanf("%d", &x);
		if (x>20) good=false;
		if (good) printf("Case %d: good\n", caseNo);
		else printf("Case %d: bad\n", caseNo);
	}
	return 0;
}