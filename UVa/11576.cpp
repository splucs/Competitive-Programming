#include <cstdio>
#include <cstring>
#define MAXN 109
//pre process P in order to get b. O(m)
void kmpPreprocess(char* P, int* b) {
	b[0] = -1;
	int m = strlen(P);
	for(int i = 0, j = -1; i < m;) {
		while (j >= 0 && P[i] != P[j]) j = b[j];
		i++; j++;
		b[i] = j;
	}
}
//kmp search. O(n+m)
int kmpSearch(char* P, char* T, int* b) {
	int n = strlen(T), m = strlen(P);
	for (int i=0, j=0; i < n;) {
		while (j >= 0 && T[i] != P[j]) j = b[j];
		i++; j++;
		if (i == n) {
			return j;
			j = b[j];
		}
	}
}

int main(){
	int n, k, w, res, b[MAXN];
	char old[MAXN], now[MAXN];
	scanf("%d", &n);
	while(n-->0){
		scanf("%d %d", &k, &w);
		res = k;
		scanf(" %s", old);
		for(int i=0; i<w-1; i++){
			scanf(" %s", now);
			kmpPreprocess(now, b);
			res += k - kmpSearch(now, old, b);
			strcpy(old, now);
		}
		printf("%d\n", res);
	}
	return 0;
}