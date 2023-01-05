#include <cstdio>
#define foreach(i, n) for(int i=0; i<n; i++)
#define MAXN 100009

int main(){
	int S, B, L, R, right[MAXN], left[MAXN];
	while(scanf("%d %d", &S, &B), (S || B)){
		foreach(i, S){
			right[i+1]=i+2;
			left[i+1]=i;
		}
		foreach(i, B){
			scanf("%d %d", &L, &R);
			right[left[L]]=right[R];
			left[right[R]]=left[L];
			if (left[L]==0) printf("* ");
			else printf("%d ", left[L]);
			if (right[R]==S+1) printf("*\n");
			else printf("%d\n", right[R]);
		}
		printf("-\n");
	}
	return 0;
}