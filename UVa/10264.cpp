#include <cstdio>
#include <algorithm>
using namespace std;
#define MAXN ((1<<15)+9)

int main()
{
	int N, w[MAXN], pot[MAXN], mx;
	while(scanf("%d", &N)!=EOF){
		for(int i=0; i< (1<<N); i++){
			scanf("%d", w+i);
		}
		for(int i=0; i<(1<<N); i++){
			pot[i]=0;
			for(int j=0; j<N; j++){
				pot[i] += w[i^(1<<j)];
			}
		}
		mx = pot[0]+pot[1];
		for(int i=0; i<(1<<N); i++){
			for(int j=0; j<N; j++){
				mx = max(mx, pot[i] + pot[i^(1<<j)]);
			}
		}
		sort(pot, pot+(1<<N));
		printf("%d\n", mx);
	}
	return 0;
}