#include <cstdio>
#define swap(a,b) {int k=a; a=b; b=k;}

int main()
{
	int T, a, b, c;
	scanf("%d", &T);
	for(int caseNo = 1; caseNo <=T; caseNo++){
		scanf("%d %d %d", &a, &b, &c);
		if (a>b) swap(a,b);
		if (a>c) swap(a,c);
		if (b>c) swap(b,c);
		printf("Case %d: %d\n", caseNo, b);
	}
	return 0;
}