#include <bits/stdc++.h>
using namespace std;

int previousp[10005];
int marked[10005];
int ord[10005];
int main() {
	int n, s, c;
	scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		scanf("%d", &previousp[i]);
		previousp[i]--;
	}
	scanf("%d %d", &s, &c);

	for (int i = 0; i < s; i++) {
		memset(marked, 0, sizeof(marked));
		bool ok = true;
		for(int j = 0; j < c; j++) {
			int node;
			scanf("%d", &node);
			node--;
			marked[node] = true;

			ord[j] = node;
		}
		for (int j = 0; j < c; j++) {
				if(!marked[previousp[ord[j]]]) {
					ok = false;
					break;
				}
			
		}
		if(ok) printf("yes\n");
		else printf("no\n");
	}
}