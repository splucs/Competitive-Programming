#include <cstdio>
#include <cstring>

int main(){
	int T, n, ans;
	scanf("%d", &T);
	char str[109];
	for (int caseNo = 1; caseNo <= T; ++caseNo)
	{
		scanf(" %s", str);
		n = strlen(str);
		ans = (int)(str[n-1]=='-');
		for (int i = 1; i < n; ++i)
		{
			if (str[i]!=str[i-1]) ans++;
		}
		printf("Case #%d: %d\n", caseNo, ans);
	}
	return 0;
}