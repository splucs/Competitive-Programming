#include <cstdio>

int main()
{
	int t, n;
	scanf("%d", &t);
	while(t-->0){
		scanf("%d", &n);
		n=(n*(567/9) + 7492)*5 - 498;
		if (n<0) n*=-1;
		printf("%d\n", (n/10)%10);
	}
	return 0;
}