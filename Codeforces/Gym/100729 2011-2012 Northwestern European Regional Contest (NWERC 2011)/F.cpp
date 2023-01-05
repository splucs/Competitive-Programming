#include <bits/stdc++.h>
using namespace std;
#define MAXS 59
#define INF (1<<30)
#define MAXN 103000
#define MAXM 900000

int ned, prv[MAXN], first[MAXN], to[MAXM], nxt[MAXM];
int cap[MAXM], dist[MAXN];

void init(){
   memset(first, -1, sizeof first);
   ned = 0;
}

void add(int u, int v, int f){
    to[ned] = v, cap[ned] = f;
    nxt[ned] = first[u];
    first[u] = ned++;
    
    to[ned] = u, cap[ned] = 0;
    nxt[ned] = first[v];
    first[v] = ned++;
}

int augment(int v, int minEdge, int s) {
	int e = prv[v];
	if (e == -1) return minEdge;
	int f = augment(to[e^1], min(minEdge, cap[e]), s);
	cap[e] -= f;
	cap[e^1] += f;
	return f;
}

bool bfs(int s, int t){
	int u, v;
	memset(&dist, -1, sizeof dist);
	dist[s] = 0;
	queue<int> q; q.push(s);
	memset(&prv, -1, sizeof prv);
	while (!q.empty()) {
		u = q.front(); q.pop();
		if (u == t) break;
		for(int e = first[u]; e!=-1; e = nxt[e]){
			v = to[e];
			if (dist[v] < 0 && cap[e] > 0) {
				dist[v] = dist[u] + 1;
				q.push(v);
				prv[v] = e;
			}
		}
	}
	return dist[t] >= 0;
}

int edmondskarp(int s, int t){
	int result = 0;
	while (bfs(s, t)) {
		result += augment(t, INF, s);
	}
	return result;
}


int D, F, B, ans;
int N, M, cnt;
char board[MAXS][MAXS];
int pos[MAXS][MAXS];
int di[4] = {0, 1, 0, -1};
int dj[4] = {-1, 0, 1, 0};

int main() {
	int T;
	scanf("%d", &T);
	while(T --> 0) {
		
		scanf("%d %d %d %d %d", &M, &N, &D, &F, &B);
		ans = 0;
		int s = cnt++;
		int t = cnt++;
		for(int i=0; i<N; i++) {
			for(int j=0; j<M; j++) {
				scanf(" %c", &board[i][j]);
				if (board[i][j] == '.' && (i == 0 || j == 0 || i == N-1 || j == M-1)) {
					board[i][j] = '#';
					ans += F;
					//printf("edge\n");
				}
				pos[i][j] = cnt++;
			}
		}
		//printf("ans = %d\n", ans);
		
		init();
		memset(&cap, 0, sizeof cap);
		for(int i=0; i<N; i++) {
			for(int j=0; j<M; j++) {
				if (board[i][j] == '.') {
					add(s, pos[i][j], F);
				}
				if (board[i][j] == '#') {
					if (i == 0 || j == 0 || i == N-1 || j == M-1) add(pos[i][j], t, INF);
					else add(pos[i][j], t, D);
				}
				for(int k=0; k<4; k++) {
					int ni = i + di[k];
					int nj = j + dj[k];
					if (ni < 0 || nj < 0 || ni > N-1 || nj > M-1) continue;
					add(pos[i][j], pos[ni][nj], B);
				}
			}
		}
		
		ans += edmondskarp(s, t);
		printf("%d\n", ans);		
	}
	
	return 0;
}