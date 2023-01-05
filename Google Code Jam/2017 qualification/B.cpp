#include <bits/stdc++.h>
using namespace std;
#define MAXN 30
#define INF ('9' + 9)

int main()
{
	char str[MAXN], *start;
	int n, T;
	scanf("%d", &T);
	for(int caseNo = 1; caseNo <= T; caseNo++){
		scanf(" %s", str);
		n = strlen(str);
		for(int i=0; i+1<n; i++){
			if (str[i] > str[i+1]){
				str[i]--;
				while(i > 0 && str[i] < str[i-1]){
					i--;
					str[i]--;
				}
				for(int j=i+1; j<n; j++){
					str[j] = '9';
				}
				break;
			}
		}
		start = str;
		while(start[0] == '0') start++;
		printf("Case #%d: %s\n", caseNo, start);
	}
	return 0;
}