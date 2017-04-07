#include <cstdio>

int main()
{
	int N, p, s;
	char l;
	scanf("%d", &N);
	while(N-->0){
		scanf("%d%c%d", &p, &l, &s);
		if (s==p) printf("%d\n", p*s);
		else if (l>='A' && l<='Z') printf("%d\n", s-p);
		else if (l>='a' && l<='z') printf("%d\n", s+p);
	}
	return 0;
}