#include <cstdio>

int main()
{
	int t, a, b;
	scanf("%d", &t);
	while(t-->0){
		scanf ("%d %d", &a, &b);
		if (a>b) printf(">\n");
		if (a<b) printf("<\n");
		if (a==b) printf("=\n");
	}
	return 0;
}