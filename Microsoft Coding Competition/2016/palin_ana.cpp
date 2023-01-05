#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int pas[25][25];

int pascal(int n, int k){
	if (pas[n][k]>=0) return pas[n][k];
	if (k>n) return pas[n][k] = 0;
	if (n==k || k==0) return pas[n][k] = 1;
	return pas[n][k] = pascal(n-1,k) + pascal(n-1, k-1);
}

int main()
{
	char str[30];
	int n, used[260], res, pos, space;
	bool hasodd;
	memset(&pas, -1, sizeof pas);
	while(scanf(" %s", str)!=EOF){
		n = strlen(str);
		memset(&used, 0, sizeof used);
		hasodd = false;
		for(int i=0; i<n; i++){
			used[(int)str[i]]++;
		}
		res=0;
		hasodd = false;
		for(int i=0; i<260; i++){
			if (used[i]%2!=0){
				if (!hasodd) hasodd = true;
				else res++;
				used[i]--;
			}
		}
		pos = 1;
		space = (n-res)/2;
		for (int i=0; i<260; i++){
			if (used[i]>0){
				pos *= pascal(space, used[i]/2);
				space -= used[i]/2;
			}
		}
		printf("%d,%d\n", res, pos);
	}
	return 0;
}