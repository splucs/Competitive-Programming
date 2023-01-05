#include <bits/stdc++.h>
using namespace std;
#define MAXN 509

map<string, int> str2id[2];
vector<string> id2str[2];
int match[MAXN], in[2][MAXN], out[2][MAXN];
bool graph[2][MAXN][MAXN], used[2][MAXN];
int gsz, N;

bool checkmatch(int u, int v) {
	if (in[0][u] != in[1][v] || out[0][u] != out[1][v]) return false;
	for(int i=0, j; i<gsz; i++) {
		j = match[i];
		if (!used[0][i] || !used[1][j]) break;
		if (graph[0][u][i] && !graph[1][v][j]) return false;
		if (graph[0][i][u] && !graph[1][j][v]) return false;
	}
	return true;
}

bool backtrack(int u) {
	if (u == gsz) return true;
	for(int i=u, j=u, v; j<gsz; j++) {
		swap(match[i], match[j]);
		v = match[u];
		//printf("trying %s->%s\n", id2str[0][u].c_str(), id2str[1][v].c_str());
		if (checkmatch(u, v)) {
			used[1][v] = true;
			used[0][u] = true;
			if (backtrack(u+1)) return true;
			used[1][v] = false;
			used[0][u] = false;
		}
		swap(match[i], match[j]);
	}
	return false;
}

int main() {
	char buffer[100];
	string cur;
	while(scanf("%d", &N), N) {
		for(int s=0; s<2; s++) {
			str2id[s].clear();
			id2str[s].clear();
			gsz = 0;
			for(int i=0; i<MAXN; i++) {
				for(int j=0; j<MAXN; j++) {
					graph[s][i][j] = false;
				}
				used[s][i] = false;
				in[s][i] = out[s][i] = 0;
				match[i] = i;
			}
			for(int i=0; i<N; i++) {
				
				scanf(" %s", buffer);
				cur = buffer;
				if (!str2id[s].count(cur)) {
					str2id[s][cur] = gsz++;
					id2str[s].push_back(cur);
				}
				int u = str2id[s][cur];
				
				scanf(" %s", buffer);
				cur = buffer;
				if (!str2id[s].count(cur)) {
					str2id[s][cur] = gsz++;
					id2str[s].push_back(cur);
				}
				int v = str2id[s][cur];
				
				graph[s][u][v] = true;
				in[s][v]++;
				out[s][u]++;
			}
		}
		
		if(!backtrack(0)) { printf("error, no solution found\n"); return 1; }
		vector<pair<string, string> > ans;
		for(int u=0, v; u<gsz; u++) {
			v = match[u];
			ans.push_back(make_pair(id2str[0][u], id2str[1][v]));
		}
		sort(ans.begin(), ans.end());
		for(int i=0; i<(int)ans.size(); i++) {
			printf("%s/%s\n", ans[i].first.c_str(), ans[i].second.c_str());
		}
		printf("\n");
	}
	return 0;
}