#include <cstdio>
#include <iostream>
#include <string>
using namespace std;

int main(){
	int N, Q, siz, k, ncomb, vet[100000];
	string songs[30];
	while(true){
		scanf("%d %d", &N, &Q);
		if (N==0 && Q==0) break;
		for (int i = 0; i < N; ++i)
		{
			cin>> songs[i];
		}
		for (int q = 0; q < Q; ++q)
		{
			scanf("%d", &k);
			siz=1;
			ncomb=N;
			while(k>siz*ncomb){
				k-=siz*ncomb;
				ncomb*=N;
				siz++;
			}
			ncomb = k/siz;
			k%=siz;
			for (int i=siz-1; i>=0; i--)
			{
				vet[i]=ncomb%N;
				ncomb/=N;
			}
			if (k==0) printf("%s\n", songs[(vet[siz-1]-1+N)%N].c_str());
			else printf("%s\n", songs[vet[(k-1+siz)%siz]].c_str());
		}
		printf("\n");
	}
	return 0;
}