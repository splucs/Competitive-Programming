#include <cstdio>
#include <string>
#include <iostream>
#include <map>
#include <algorithm>
using namespace std;
typedef struct node{
	int h;
	int r;
	int m;
	int c;
} node;

bool operator <(const node a, const node b){
	return a.r<b.r;
}
bool operator >(const node a, const node b){
	return a.r>b.r;
}

int maxint(int a, int b){
	if (a>b) return a;
	else return b;
}


int main()
{
	int N, M;
	node vet[1009];
	string str;
	while (true){
		scanf("%d", &N);
		if (N==0) break;
		M = 0;
		for (int i = 0; i < N; ++i)
		{
			cin >> vet[i].h >> vet[i].r >> str;
			vet[i].m=vet[i].h;
			M = maxint(M, vet[i].m);
			if (str=="VERMELHO") vet[i].c = 0;
			if (str=="LARANJA") vet[i].c = 1;
			if (str=="AZUL") vet[i].c = 2;
			if (str=="VERDE") vet[i].c = 3;
		}
		sort(vet, vet+N);
		for (int i=0; i<N; i++){
			for (int j=i+1; j<N; j++){
				if ((vet[i].c+1)%4!=vet[j].c && vet[i].r<vet[j].r){
					vet[j].m = maxint(vet[j].m, vet[i].m + vet[j].h);
					M = maxint(M, vet[j].m);
				}
			}
		}
		printf("%d centimetro(s)\n", M);
	}
	return 0;
}