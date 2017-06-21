#include <cstdio>
#include <cmath>

typedef unsigned long long int ull;

ull minull(ull a, ull b){
	return (a<b?a:b);
}

int main()
{
	ull N, B, n, x, y;
	scanf("%llu %llu", &N, &B);
	n = 2 + sqrt(N*N - B);
	if ((N-n)%2!=0) n++;
	n+=2;
	if (n>N) n=N;
	x = y = (N-n)/2 +1;
	B -=N*N - n*n + 1;
	while(B>0){
		if (B>0){
			x+=minull(n-1,B);
			B-=minull(n-1,B);
		}
		if (B>0){
			y+=minull(n-1,B);
			B-=minull(n-1,B);
		}
		if (B>0){
			x-=minull(n-1,B);
			B-=minull(n-1,B);
		}
		if (B>0){
			y-=minull(n-2,B);
			B-=minull(n-2,B);
		}
		if(B>0){
			x++;
			B--;
		}
		n-=2;
	}
	printf("%llu %llu\n", y, x);
	return 0;
}