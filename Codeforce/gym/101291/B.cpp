#include <bits/stdc++.h>
using namespace std;
#define MAXN 20

int w[MAXN], bar[MAXN], n, m;
vector<int> sideweights, finalweights;

void backtrack(int i, int lw, int rw)
{
	if (i == m)
	{
		if (lw == rw) sideweights.push_back(lw + rw);
		return;
	}
	backtrack(i+1, lw + w[i], rw);
	backtrack(i+1, lw, rw + w[i]);
	backtrack(i+1, lw, rw);
}

int main()
{
	scanf("%d %d", &n, &m);
	for(int i=0; i<n; i++){
		scanf("%d", bar+i);
	}
	for(int i=0; i<m; i++){
		scanf("%d", w+i);
	}

	backtrack(0, 0, 0);

	for(int i=0; i<(int)sideweights.size(); i++){
		for(int j=0; j<n; j++){
			finalweights.push_back(bar[j] + sideweights[i]);
		}
	}
	sort(finalweights.begin(), finalweights.end());
	
	for(int i=0; i<(int)finalweights.size(); i++){
		if (i > 0 && finalweights[i] == finalweights[i-1]) continue;
		printf("%d\n", finalweights[i]);
	}
	return 0;
}