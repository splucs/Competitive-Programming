#include <cstdio>

int main()
{
	int t, n, min=-1, max=101, x;
	scanf("%d", &t);
	while(t-->0){
		scanf("%d", &n);
		min=101, max=-101;
		for(int i=0; i<n; i++){
			scanf("%d", &x);
			if (min>x) min=x;
			if (max<x) max=x;
		}
		printf("%d\n", 2*(max-min));
	}
	return 0;
}