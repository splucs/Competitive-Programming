#include <cstdio>
#define MAXN 100009

int N, T;
int t[MAXN];

int main(){
	scanf("%d %d", &N, &T);
	for(int i=1; i<=N; i++){
		scanf("%d", &t[i]);
	}
	int left = T, k=1, yan = 0;
	while(k<=N && t[k] <= left){
		left -= t[k];
		k++;
		yan++;
	}
	int nathan = 0;
	left = T, k=N;
	while(k>0 && t[k] <= left){
		left -= t[k];
		nathan++;
		k--;
	}
	if (yan > nathan) printf("Yan\n");
	else if (yan < nathan) printf("Nathan\n");
	else printf("Empate\n");
	return 0;
}