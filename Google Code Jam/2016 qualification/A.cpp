#include <cstdio>
#include <cstring>

bool count[10];
int ap;

void update(long long int N){
	long long int p;
	while(N > 0){
		p = N%10;
		N/=10;
		if (!count[p]){
			count[p]=true;
			ap++;
		}
	}
}

int main()
{
	int T;
	long long int N, aux;
	scanf("%d", &T);
	for(int caseNo = 1; caseNo <= T; caseNo++){
		scanf("%lld", &N);
		if (N==0){
			printf("Case #%d: INSOMNIA\n", caseNo);
			continue;
		}
		ap = 0;
		aux = 0;
		memset(&count, false, sizeof count);
		while(ap<10){
			aux+=N;
			update(aux);
		}
		
		printf("Case #%d: %lld\n", caseNo, aux);
	}
	return 0;
}