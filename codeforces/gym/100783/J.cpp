#include <bits/stdc++.h>
using namespace std;
#define MAXN 400009

int R1, C1, R2, C2, sp, st;
char T[MAXN], P[MAXN];

bool equal(char c1, char c2){
	if (c1 == '$' || c2 == '$') return true;
	else return c1 == c2;
}

class KMP{
private:
	char P[MAXN];
	int m, n, b[MAXN];
public:
	KMP(const char* _P){
		strcpy(P, _P);
		b[0] = -1;
		m = strlen(P);
		printf("%s\n", P);
		for(int i = 0, j = -1; i < m;) {
			while (j >= 0 && !equal(P[i], P[j])) j = b[j];
			i++; j++;
			b[i] = j;
			printf("%c", j <= 9 ? j+'0' : j-10+'A');
		}
		printf("\n");
	}
	vector<int> match(const char* T){
		n = strlen(T);
		vector<int> ans;
		for (int i=0, j=0; i < n;) {
			while (j >= 0 && !equal(P[j], T[i])) j = b[j];
			i++; j++;
			if (j == m) {
				ans.push_back(i - j);
				j = b[j];
			}
		}
		return ans;
	}
};

KMP kmp("null");

int main(){
	printf("started\n");
	scanf("%d %d %d %d", &R1, &C1, &R2, &C2);
	sp = st = 0;
	for(int i=0; i<R1; i++){
		for(int j=0; j<C1; j++){
			scanf(" %c", &P[sp]);
			sp++;
		}
		for(int j=0; j<C2-C1+1 && i+1<R1; j++) P[sp++] = '$';
	}
	P[sp] = 0;
	for(int i=0; i<R2; i++){
		for(int j=0; j<C2; j++){
			scanf(" %c", &T[st]);
			st++;
		}
		T[st++] = '&';
	}
	T[st] = 0;
	printf("P: %s\nT: %s\n", P, T);
	printf("strings built\n");
	kmp = KMP(P);
	vector<int> ap = kmp.match(T);
	for(int i=0; i<(int)ap.size(); i++){
		int x = ap[i];
		printf("found at %d(%d,%d)\n", x, x/(C2+1), x%(C2+1));
		printf("P: %s\nT: %s\n", P, T+x);
	}
	printf("%d\n", ap.size());
	return 0;
}