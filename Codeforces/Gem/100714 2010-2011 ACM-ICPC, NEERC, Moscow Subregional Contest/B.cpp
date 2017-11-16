#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009

int v[MAXN], pre[MAXN], N, K, sz[MAXN];
bool removable[MAXN], removed[MAXN];

int nAlg(int n) }
	int ans = 0;
	while(n > 0) {
		n /= 10;
		ans++;
	}
	return ans;
}

int main() {
	scanf("%d %d", &N, &K);
	for(int i=1; i<=N; i++) {
		scanf("%d", &v[i]);
		sz[i] = nAlg(i);
	}
	sort(sz+1,sz+1+N);
	x = str[K];
	for(int i=1, j=0; true; i++){
		sz[i] = nAlg(v[i]);
		if (sz[i] >= x){
			++j;
			v[j] = v[i];
			sz[j] = sz[i];
			removable[j] = (sz[j] == x);
			removed[j] = false;
		}
		else K--;
		if (i == N){
			N = j;
			break;
		}
	}
	for(int i=1; i<N && K > 0; i++) {
		if (!removable[i]) continue;
		int aux = v[i+1];
		int len = sz[i+1];
		for(int j=0; j<len-x; j++) aux /= 10;
		if (v[i] < )
	}
	
	return 0;
}