#include <bits/stdc++.h>
using namespace std;
#define MAXN 609

int N, L, M, len;
char buffer[20];
typedef long long ll;
map<string, int> s2id;
vector<int> adjList[MAXN];
int msz;
int reduce(string s) {
	if (!s2id.count(s)) {
		adjList[msz].clear();
		s2id[s] = msz++;
	}
	return s2id[s];
}

ll dp[MAXN][MAXN];

int main() {
	int u, v;
	while(scanf("%d %d %d", &N, &L, &M), N || L || M) {
		msz = 0;
		s2id.clear();
		while(M-->0) {
			scanf(" %s", buffer);
			len = strlen(buffer);
			if (len > 1) {
				v = reduce(string(buffer+1));
				buffer[len-1] = 0;
				u = reduce(string(buffer));
				adjList[u].push_back(v);
			}
			else {
				reduce(string(buffer));
			}
		}
		if (len == 1) {
			ll ans = 1;
			for(int i=0; i<L; i++) ans *= msz;
			printf("%I64d\n", ans);
			continue;
		}
		for(int k=0; k<=L-len+1; k++) {
			for(u=0; u<msz; u++) {
				if (k == 0) dp[u][k] = 1;
				else {
					dp[u][k] = 0;
					for(int i=0; i<(int)adjList[u].size(); i++) {
						v = adjList[u][i];
						dp[u][k] += dp[v][k-1];
					}
				}
			}
		}
		ll ans = 0;
		for(u=0; u<msz && L-len >= 0; u++) ans += dp[u][L-len+1];
		printf("%I64d\n", ans);
	}
	return 0;
}