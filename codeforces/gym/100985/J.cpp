#include <cstdio>
#define MAXN 1009

int sqr(int x){
	return x*x;
}

struct circle{
	int x, y, r;
	bool intersects(circle c){
		return sqr(r+c.r) == sqr(x-c.x) + sqr(y-c.y);
	}
} circles[MAXN];

int main(){
	int N;
	scanf("%d", &N);
	for(int i=1; i<=N; i++){
		scanf("%d %d %d", &circles[i].x, &circles[i].y, &circles[i].r);
		for(int j=1; j<i; j++){
			if (circles[i].intersects(circles[j])) printf("%d %d\n", j, i);
		}
	}
	return 0;
}