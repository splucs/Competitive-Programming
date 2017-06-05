#include <bits/stdc++.h>
using namespace std;
#define MAXN 

bool adj[27][27];
char s1[100], s2[100];

int main() {
	int n, q;
	char u, v;
	scanf("%d %d", &n, &q);
	for(int i=0; i<n; i++) {
		scanf(" %c %c", &u, &v);
		u-='a'; v-='a';
		adj[u][v] = true;
	}
	for(int i=0; i<27; i++) adj[i][i] = true;
	for(int k=0; k<27; k++) {
		for(int i=0; i<27; i++){
			for(int j=0; j<27; j++){
				adj[i][j] = adj[i][j] || (adj[i][k] && adj[k][j]);
			}
		}
	}
	for(int j=0; j<q; j++) {
		scanf(" %s %s", s1, s2);
		bool possible = true;
		if (strlen(s1)!=strlen(s2)) {
			possible = false;;
		}
		n = strlen(s1);
		for(int i=0; i<n; i++) {
			u = s1[i]-'a';
			v = s2[i]-'a';
			if (!adj[u][v]) possible = false;
		}
		if (possible) printf("yes\n");
		else printf("no\n");
	}
	return 0;
}