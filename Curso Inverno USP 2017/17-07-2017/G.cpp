#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009
#define INF (1<<20)

char str[MAXN][20], word[20], buffer1[20], buffer2[20], buffer[20];
int dist[MAXN][MAXN], dist0[MAXN], dist1[MAXN];

int main() {
	int N, len;
	queue<int> q;
	
	while(scanf(" %d", &N) != EOF) {
		for(int i=0; i<N; i++) {
			scanf(" %s", str[i]);
		}
		len = strlen(str[0]);
		for(int i=0; i<N; i++) {
			dist0[i] = dist1[i] = INF;
			for(int j=0; j<N; j++) {
				dist[i][j] = 0;
				for(int k=0; k<len; k++){
					if (str[i][k] != str[j][k]) dist[i][j]++;
				}
			}
		}
		
		dist0[0] = 0;
		q.push(0);
		while(!q.empty()) {
			int u = q.front();
			q.pop();
			for(int v=0; v<N; v++) {
				if (dist[u][v] != 1) continue;
				if (dist0[v] > dist0[u] + 1) {
					dist0[v] = dist0[u] + 1;
					q.push(v);
				}
			}
		}
	
		dist1[1] = 0;
		q.push(1);
		while(!q.empty()) {
			int u = q.front();
			q.pop();
			for(int v=0; v<N; v++) {
				if (dist[u][v] != 1) continue;
				if (dist1[v] > dist1[u] + 1) {
					dist1[v] = dist1[u] + 1;
					q.push(v);
				}
			}
		}
		
		int ans = INF;
		for(int u=0; u<N; u++) {
			for(int v=0; v<N; v++) {
				if (dist[u][v] == 2 && ans >= dist0[u] + dist1[v] + 2) {
					strcpy(buffer1, str[u]);
					for(int k=0; k<len; k++) {
						if (str[u][k] != str[v][k]){
							buffer1[k] = str[v][k];
							break;
						}
					}
					strcpy(buffer2, str[v]);
					for(int k=0; k<len; k++) {
						if (str[u][k] != str[v][k]){
							buffer2[k] = str[u][k];
							break;
						}
					}
					if (strcmp(buffer1, buffer2) < 0) strcpy(buffer, buffer1);
					else strcpy(buffer, buffer2);
					
					if (ans == dist0[u] + dist1[v] + 2 && strcmp(buffer, word) < 0) {
						strcpy(word, buffer);
					}
					if (ans > dist0[u] + dist1[v] + 2) strcpy(word, buffer);
					ans = dist0[u] + dist1[v] + 2;
					//printf("possible new edge between %s and %s: %s\n", str[u], str[v], buffer);
				}
			}
		}
		if (ans >= dist0[1] && dist0[1] < INF) {
			printf("0\n%d\n", dist0[1]);
		}
		else if (ans == INF) {
			printf("0\n-1\n");
		}
		else {
			printf("%s\n%d\n", word, ans);
		}
	}
	return 0;
}