#include <bits/stdc++.h>
using namespace std;
#define MAXN 109

char txt[MAXN], key[MAXN], mat[MAXN][MAXN];
int id[MAXN], inv[MAXN];

bool comp(int i, int j) {
	if (key[i] != key[j]) return key[i] < key[j];
	return i < j;
}

int main() {
	int N, M;
	while(scanf(" %s", key), strcmp(key, "THEEND") != 0) {
		scanf(" %s", txt);
		M = strlen(key);
		N = strlen(txt)/M;
		for(int i=0; i<M; i++) id[i] = i;
		sort(id, id+M, comp);
		for(int i=0; i<M; i++) inv[id[i]] = i;
		for(int j=0; j<M; j++) {
			for(int i=0; i<N; i++) {
				mat[i][j] = txt[N*inv[j] + i];
			}
		}
		for(int i=0; i<N; i++) {
			for(int j=0; j<M; j++) {
				printf("%c", mat[i][j]);
			}
		}
		printf("\n");
	}
	return 0;
}