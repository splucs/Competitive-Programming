#include <bits/stdc++.h>
using namespace std;
#define MAXN 2009
#define INF 1e+18
#define EPS 1e-9

map<string, int> name2id;
char buffer[30];
int nid, N;
int from[MAXN], to[MAXN], depart[MAXN], duration[MAXN], prob[MAXN], maxdelay[MAXN];
double best[MAXN][60];
vector<int> adjList[MAXN];

int reduce(string name) {
	if (!name2id.count(name)) {
		name2id[name] = ++nid;
		adjList[nid].clear();
	}
	return name2id[name];
}

int main () {
	
	int T;
	scanf("%d", &T);
	
	while (T --> 0) {
		
		name2id.clear();
		nid = 0;
		int s, t;
		scanf(" %s", buffer);
		s = reduce(string(buffer));
		scanf(" %s", buffer);
		t = reduce(string(buffer));
		scanf(" %d", &N);
		for(int j=0; j<N; j++) {
			scanf(" %s", buffer);
			from[j] = reduce(string(buffer));
			scanf(" %s", buffer);
			to[j] = reduce(string(buffer));
			adjList[to[j]].push_back(j);
			scanf(" %d %d %d %d", &depart[j], &duration[j], &prob[j], &maxdelay[j]);
		}
		
		for(int i=1; i<=nid; i++) {
			for(int j=0; j<60; j++) {
				best[i][j] = (i == t ? 0 : INF);
			}
		}
		
		queue<int> q;
		q.push(t);
		
		do {
			int v = q.front();
			q.pop();
			
			for(int it = 0, j; it < (int)adjList[v].size(); it++) {
				j = adjList[v][it];
			
				double nodelaytime = best[to[j]][(depart[j] + duration[j]) % 60] + duration[j];
				double delaytime = 0.0;
				
				for(int t=1; t<=maxdelay[j]; t++) {
					delaytime += best[to[j]][(depart[j] + duration[j] + t) % 60] + duration[j] + t;
				}
				delaytime /= maxdelay[j];
				
				double expectedtime = prob[j]*delaytime + (100 - prob[j])*nodelaytime;
				expectedtime /= 100.0;
				
				bool change = false;
				for (int t=0; t<60; t++) {
					if (best[from[j]][(depart[j] - t + 60) % 60] > expectedtime + t) {
						best[from[j]][(depart[j] - t + 60) % 60] = expectedtime + t;
						change = true;
					}
				}
				if (change) q.push(from[j]);
			}
			
		} while(!q.empty());
		
		double arrive = INF;
		for(int t=0; t<60; t++) {
			if (arrive > best[s][t]) {
				arrive = best[s][t];
			}
		}
	
		if (arrive > 1e+10) printf("IMPOSSIBLE\n");
		else printf("%.7f\n", arrive);
	}
	
	return 0;
}