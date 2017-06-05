#include <cstdio>

int main()
{
	int t, n, m;
	scanf("%d", &t);
	while(t-->0){
		scanf("%d %d", &n, &m);
		n-=2;
		m-=2;
		if (n%3==0) n/=3;
		else n=(n/3)+1;
		if (m%3==0) m/=3;
		else m=(m/3)+1;
		printf("%d\n", n*m);
	}
	return 0;
}