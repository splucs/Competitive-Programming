#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009

char line[MAXN], sym[MAXN], ans[MAXN];

int main() {
	freopen("important.in", "r", stdin);
	freopen("important.out", "w", stdout);
	
	int n;
	scanf("%d", &n);
	ans[0] = 0;
	while(n--){
		scanf(" ");
		gets(line);
		sscanf(line, " %s", sym);
		sym[1] = 0;
		strcat(ans, sym);
		strcat(ans, "&");
	}
	n = strlen(ans);
	ans[n-1] = 0;
	printf("Yes\n%s <=> %s\n", ans, ans);
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}