#include <cstdio>
#include <cstdlib>

int main(){
	int x, y, a, q;
	scanf("%d %d", &x, &y);
	while(true){
		if (y>x){
			printf("2 %d\n", y-x);
			y=x;
		}
		else if (y<x){
			printf("1 %d\n", x-y);
			x=y;
		}
		else printf("1 1\n");
		fflush(stdout);
		if (x == 0 && y == 0) break;
		scanf("%d %d", &a, &q);
		if (a == 1) x -= q;
		else if (a == 2) y -= q;
	}
	return 0;
}