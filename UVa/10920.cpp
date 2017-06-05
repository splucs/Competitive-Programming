#include <cstdio>
#include <cmath>

typedef long long int ll;

int main(){
	ll SZ, P, layer, x, y, n;
	while(scanf("%lld %lld", &SZ, &P), (SZ || P)){
		if (P==1){
			printf("Line = %lld, column = %lld.\n", SZ/2 + 1, SZ/2 + 1);
			continue;
		}
		layer = sqrt(P);
		if (layer%2==0) layer--;
		while(P>layer*layer){
			layer+=2;
		}
		x = (layer-1)/2 + SZ/2;
		y = (layer-1)/2 + SZ/2 + 1;
		n = (layer-2)*(layer-2)+1;
		while(n<P){
			n++;
			if (y>=x && SZ-y+1<x) x--;
			else if (y>x && SZ-y+1>=x) y--;
			else if (y<=x && SZ-y+1>x) x++;
			else y++;
		}
		printf("Line = %lld, column = %lld.\n", y, x);
	}
	return 0;
}