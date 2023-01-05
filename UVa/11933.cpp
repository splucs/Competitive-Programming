#include <cstdio>

int main()
{
	int n, a, b;
	bool isa;
	while(scanf("%d", &n), n){
		a=b=0;
		isa = true;
		while(n>0){
			if (isa) a += (n & -n);
			else b += (n & -n);
			n -= (n & -n);
			isa = !isa;
		}
		printf("%d %d\n", a, b);
	}
	return 0;
}