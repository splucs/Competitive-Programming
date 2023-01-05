#include <cstdio>
#include <cstring>
using namespace std;
#define MAXN 500009

int P[MAXN], T[MAXN], n, m;
int b[MAXN], vet[MAXN];
char str[MAXN];

bool prematch(int i, int j){
	//printf("pre comparing T[%d] = %d and P[%d] = %d\n", i, T[i], j, P[j]);
	if (P[i] == P[j]) return true;
	if (P[j] == -1 && j-P[i] < 0) return true;
	return false;
}

void kmpPreprocess() {
	b[0] = -1;
	for(int i = 0, j = -1; i < m;) {
		while (j >= 0 && !prematch(i, j)) j = b[j];
		i++; j++;
		b[i] = j;
	}
}

bool match(int i, int j){
	//printf("comparing T[%d] = %d and P[%d] = %d\n", i, T[i], j, P[j]);
	if (T[i] == P[j]) return true;
	if (P[j] == -1 && j-T[i] < 0) return true;
	return false;
}

/*void printmatch(int si, int sj){
	for(int i=0; i<n; i++){
		printf("%2d", T[i]);
		if (si == i) printf("O");
		else printf(" ");
	}
	printf("\n");
	for(int j=0; j<si-sj; j++) printf("   ");
	for(int j=0; j<m; j++){
		printf("%2d", P[j]);
		if (sj == j) printf("O");
		else printf(" ");
	}
	printf("\n");	
}*/

int kmpSearch() {
	//int n = strlen(T), m = strlen(P);
	int nmatches = 0;
	for (int i=0, j=0; i < n;) {
		while (j >= 0 && !match(i, j)){
			//printmatch(i, j);
			j = b[j];
		}
		//printmatch(i, j);
		i++; j++;
		if (j == m) {
			//printf("found at pos %d\n", i-j);
			nmatches++;
			j = b[j];
		}
	}
	return nmatches;
}

int main(){
	scanf("%s", str);
	n = strlen(str);
	scanf("%d", &m);
	for(int i=0; i<m; i++){
		scanf("%d", &vet[i]);
	}
	int lastpos[300];
	memset(&lastpos, -1, sizeof lastpos);
	for(int i=0; i<n; i++){
		if (lastpos[str[i]] != -1){
			T[i] = i - lastpos[str[i]];
		}
		else T[i] = -1;
		lastpos[str[i]] = i;
	}
	memset(&lastpos, -1, sizeof lastpos);
	for(int i=0; i<n; i++){
		if (lastpos[vet[i]] != -1){
			P[i] = i - lastpos[vet[i]];
		}
		else P[i] = -1;
		lastpos[vet[i]] = i;
	}
		/*printf("%s\n", str);
		for(int i=0; i<n; i++){
			printf("%d", i%10);
		}
		printf("\n");*/
	kmpPreprocess();
		/*printf("b: ");
		for(int i=0; i<=m; i++){
			printf("%2d ", b[i]);
		}
		printf("\n");*/
	int ans = kmpSearch();
	printf("%d\n", ans);
	return 0;
}