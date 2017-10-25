#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
typedef pair<int,int> ii;

int esq[MAXN], dir[MAXN], vec[MAXN];
char sol[MAXN];

int main() {
	int n;
	while(scanf("%d", &n) != EOF) {
		memset(esq, 0, sizeof(esq));
		memset(dir, 0, sizeof(dir));
		for (int i = 1; i <= n; i++) {
			scanf("%d", &vec[i]);
		}
		for (int i = 1; i <= n; i++) {
			esq[i] = esq[i-1] + vec[i];
		}
		
		for (int i = n; i >= 1; i--) {
			dir[i] = dir[i+1] + vec[i];
		}
		int k = 0, sum = dir[n/2+1];
		for (int i = 1; i <= n/2; i++) {
			if (esq[i] + dir[n/2+1+i] > sum) {
				sum = esq[i] + dir[n/2+1+i];
				k = i;
			}
		}
		sol[n/2] = '\0';
		for (int i = 0; i < k; i++) sol[i] = 'L';
		for (int i = k; i < n/2; i++) sol[i] = 'R';
		printf("%d\n%s\n", sum, sol);
	}
}