#include <cstdio>
#include <cstring>
#define MAXN 109

int b[MAXN], l, n, m;
char P[MAXN], T[MAXN], text[MAXN][MAXN];
//preprocessamento de P para obter b. O(m)
void kmpPreprocess() {
	b[0] = -1;
	for(int i = 0, j = -1; i < m;) {
		while (j >= 0 && P[i] != P[j]) j = b[j];
		i++; j++;
		b[i] = j;
	}
}
int kmpSearch() {
	for (int i=0, j=0; i < n;) {
		while (j >= 0 && T[i] != P[j]) j = b[j];
		i++; j++;
		if (j == m) {
			return i - j;
			j = b[j];
		}
	}
	return -1;
}

int main(){
	int x, k;
	scanf(" %d", &l);
	while(l>0){
		for (int i = 0; i < l; ++i){
			for (int j = 0; j < l; ++j){
				scanf(" %c", &text[i][j]);
			}
		}
		while(scanf(" %s", P), (P[0]<'0' || P[0]>'9')){
			m = strlen(P);
			kmpPreprocess();
			x = -1;
			//horizontal
			for(int i=0; i<l && x<0; i++){
				for(k=0; k<l; k++) T[k]=text[i][k];
				n=l;
				x = kmpSearch();
				if (x>=0) printf("%d,%d %d,%d\n", i+1, x+1, i+1, x+m);
			}
			for(int i=0; i<l && x<0; i++){
				for(k=0; k<l; k++) T[l-1-k]=text[i][k];
				n=l;
				x = kmpSearch();
				if (x>=0) printf("%d,%d %d,%d\n", i+1, l-x, i+1, l-x-m+1);
			}
			//vertical
			for(int i=0; i<l && x<0; i++){
				for(k=0; k<l; k++) T[k]=text[k][i];
				n=l;
				x = kmpSearch();
				if (x>=0) printf("%d,%d %d,%d\n", x+1, i+1, x+m, i+1);
			}
			//diagonal principal
			for(int i=0; i<l && x<0; i++){
				for(k=0; k+i<l; k++) T[k]=text[i+k][k];
				n = l-i;
				x = kmpSearch();
				if (x>=0) printf("%d,%d %d,%d\n", i+x+1, x+1, i+x+m, x+m);
			}
			for(int i=0; i<l && x<0; i++){
				for(k=0; k+i<l; k++) T[k]=text[k][i+k];
				n = l-i;
				x = kmpSearch();
				if (x>=0) printf("%d,%d %d,%d\n", x+1, i+x+1, x+m, i+x+m);
			}
			//diagonal secundaria
			for(int i=0; i<l && x<0; i++){
				for(k=0; k+i<l; k++) T[k]=text[i+k][l-1-k];
				n = l-i;
				x = kmpSearch();
				if (x>=0) printf("%d,%d %d,%d\n", i+x+1, l-x, i+x+m, l-x-m+1);
			}
			for(int i=0; i<l && x<0; i++){
				for(k=0; k+i<l; k++) T[k]=text[k][l-1-i-k];
				n = l-i;
				x = kmpSearch();
				if (x>=0) printf("%d,%d %d,%d\n", x+1, l-i-x, x+m, l-i-x-m+1);
			}
			if (x<0) printf("Not found\n");
		}
		l = (int)(P[0]-'0');
	}
	return 0;
}