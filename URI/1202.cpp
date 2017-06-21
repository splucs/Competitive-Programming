#include <cstdio>
#include <cstring>
/*#include <map>
using namespace std;

typedef struct resto
{
	int r1;
	int r2;
} resto;

bool operator < (resto a, resto b){
	if (a.r1!=b.r1) return a.r1<b.r1;
	else return a.r2<b.r2;
}

bool operator > (resto a, resto b){
	if (a.r1!=b.r1) return a.r1>b.r1;
	else return a.r2>b.r2;
}

bool operator ==(resto a, resto b){
	return a.r1==b.r1 && b.r2==a.r2;
}

resto createResto(int n1, int n2){
	resto r;
	r.r1=n1;
	r.r2=n2;
	return r;
}*/

int main()
{
	int T, len, num, cont;
	char seq[10009];
	int fib[1500];
	fib[0]=0;
	fib[1]=1;
	/*map<resto, int> restos;
	resto r = createResto(fib[1], fib[0]);
	restos[r]=1;*/
	for (int i = 2; i < 1500; ++i)
	{
		fib[i]=(fib[i-1]+fib[i-2])%1000;
		/*r=createResto(fib[i], fib[i-1]);
		if (!restos.count(r)) restos[r]=i;
		else{
			printf("resto do fib[%d] = resto do fib[%d]\n", i, restos[r]);
			break;
		}*/
	}
	scanf("%d", &T);
	while(T-->0){
		scanf(" %s", seq);
		len = strlen(seq);
		cont=1;
		num=0;
		for (int i = len-1; i >=0; --i)
		{
			num+=(seq[i]-'0')*cont;
			cont*=2;
			num%=1500;
			cont%=1500;
		}
		printf("%03d\n", fib[num]);
	}
	return 0;
}