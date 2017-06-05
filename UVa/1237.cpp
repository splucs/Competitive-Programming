#include <cstdio>
#include <cstring>
#define MAXN 100009

struct car{
	char name[29];
	int low;
	int high;
} cars[MAXN];

int main(){
	int T, D, Q, P, ans;
	scanf("%d", &T);
	while(T-->0){
		scanf("%d", &D);
		for(int i=0; i<D; i++){
			scanf(" %s %d %d", cars[i].name, &cars[i].low, &cars[i].high);
		}
		scanf("%d", &Q);
		for(int i=0; i<Q; i++){
			scanf("%d", &P);
			ans = -1;
			for(int j=0; j<D; j++){
				if (P >= cars[j].low && P <= cars[j].high){
					if (ans==-1) ans = j;
					else ans = -2;
				}
			}
			if (ans>=0) printf("%s\n", cars[ans].name);
			else printf("UNDETERMINED\n");
		}
		if (T>0) printf("\n");
	}
	return 0;
}