#include <bits/stdc++.h>
using namespace std;

int nAlgarismos(int n){
	int ans = 0;
	while(n > 0){
		ans++;
		n /= 10;
	}
	return ans;
}

int main()
{
	int N;
	while(scanf("%d", &N), N) {
		int nesp = nAlgarismos(1 << (2*N-2)), nalg;
		for(int i=0; i<N; i++) {
			for(int j=0; j<N; j++) {
				nalg = nAlgarismos(1<<(i+j));
				for(int k=0; k<nesp-nalg; k++) printf(" ");
				printf("%d", 1<<(i+j));
				if (j+1 < N) printf(" ");
				else printf("\n");
			}
		}
		printf("\n");
	}
	return 0;
}