#include <bits/stdc++.h>
using namespace std;

int main()
{
	int N;
	bool possible;
	while(scanf("%d", &N)!=EOF) {
		possible = false;
		for(int i = 0, j; i*i <= N; i++) {
			j = sqrt(N - i*i);
			if (i*i + j*j == N) possible = true;
		}
		if (possible) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}