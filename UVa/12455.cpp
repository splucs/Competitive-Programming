#include <cstdio>
#include <cstring>

int t, n, p, size[30];
bool dp[30][1009], calculated[30][1009];

bool DP(int pos, int left){
	if (left<0) return false;
	if (left==0) return true;
	if (pos==p) return false;
	if (calculated[pos][left]) return dp[pos][left];
	calculated[pos][left] = true;
	dp[pos][left] = DP(pos+1, left) || DP(pos+1, left - size[pos]);
	return dp[pos][left];
}

int main()
{
	scanf("%d", &t);
	while(t-->0){
		scanf("%d %d", &n, &p);
		for(int i=0; i<p; i++){
			scanf("%d", size+i);
		}
		memset(&calculated, false, sizeof calculated);
		if (DP(0, n)) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}