#include <stdio.h>

char mat[1005][105];
char consulta[105];

int main() {
	int n, m, q, k, cnt;
	scanf("%d %d %d %d", &n, &m, &q, &k);
	k = m-k;
	for (int i = 0; i < n; i++) {
		scanf(" %s", mat[i]);
	}
	for (int i = 0; i < q; i++) {
		scanf(" %s", consulta);
		cnt = 0;
		for (int j = 0; j < n && cnt < k; j++) {
			cnt = 0;
			for (int z = 0; z < m; z++) {
				if(mat[j][z] == consulta[z]) cnt++;
			}
		}
		
		if (cnt >= k) printf("S\n");
		else printf("N\n");
	}
	
}