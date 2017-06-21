#include <cstdio>

int main()
{
	int N, LA, LB, SA, SB;
	scanf("%d %d %d %d %d", &N, &LA, &LB, &SA, &SB);
	if(N>=LA && N>=SA && N<=LB && N<=SB) printf("possivel\n");
	else printf("impossivel\n");
	return 0;
}