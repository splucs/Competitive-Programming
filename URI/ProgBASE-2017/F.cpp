#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009

char str[MAXN], s[MAXN];
double pos[MAXN];
int k, o;

void applyop(char op) {
	double p1 = pos[--k];
	double p2 = pos[--k];
	//printf("applied %c, k=%d\n", op, k);
	if (op == '-') pos[k++] = p1+p2;
	else if (op == '|') pos[k++] = p1*p2/(p1+p2);
}

void printpos() {
	printf("pos (%d):", k);
	for(int j=0; j<k; j++) printf(" %.3f", pos[j]);
	printf("\n");
}

void printop() {
	printf("op (%d):", o);
	for(int j=0; j<k; j++) printf(" %c", s[j]);
	printf("\n");
}

int main() {
	while(scanf(" %s", str) != EOF) {
		int len = strlen(str), num;
		k = o = 0;
		for(int i=0; i<len; i++) {
			if (str[i] >= '0' && str[i] <= '9') {
				sscanf(str+i, "%d", &num);
				pos[k++] = num;
				while(str[i] >= '0' && str[i] <= '9') i++;
				i--;
			}
			else {
				while(o > 0 && s[o-1] != '(' && str[i] != '(') {
					applyop(s[--o]);
				}
				if (str[i] == ')') o--;
				else s[o++] = str[i];
			}
			//printpos();
			//printop();
		}
		while(o > 0) {
			applyop(s[--o]);
		}
		//printpos();
		//printop();
		printf("%.3f\n", pos[0]);
	}
	return 0;
}