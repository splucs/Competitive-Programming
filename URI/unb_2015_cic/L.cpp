#include <bits/stdc++.h>
using namespace std;
#define MAXN 20
#define MAXM 5009
#define INF (1<<25)
#define state dp[mask][i]

int M, V, E, C, L;
int dmg[MAXM], mana[MAXM];
int minmana[MAXM][MAXM];
int dist[MAXN][MAXN], reqmask[MAXN][MAXN];
int dp[(1<<MAXN) + 1][MAXN];

//given enemy hp, min mana to kill with first h habilities
int MinMana(int hp, int h){
	if (hp <= 0) return 0;
	if (h < 0) return INF;
	if (minmana[hp][h] >= 0) return minmana[hp][h];
	return minmana[hp][h] = min(mana[h] + MinMana(hp-dmg[h], h), MinMana(hp, h-1));
}

int level[MAXN];

int mask2level(int mask) {
	int ans = 0;
	for(int i=0; i<L; i++) {
		if (mask & (1<<level[i])) ans |= (1<<i);
	}
	return ans;
}

int coin[MAXN];

int mask2coin(int mask) {
	int ans = 0;
	for(int i=0; i<C; i++) {
		if (mask & (1<<coin[i])) ans |= (1<<i);
	}
	return ans;
}


int main() {
	int a, b, m, l;
	while(scanf("%d %d %d %d %d", &M, &V, &E, &C, &L) != EOF) {
		for(int h=0; h<M; h++){
			scanf("%d %d", &dmg[h], &mana[h]);
		}
		memset(&minmana, -1, sizeof minmana);	//reset dp
		for(int i=0; i<V; i++){
			for(int j=0; j<V; j++){
				dist[i][j] = INF;
				reqmask[i][j] = 0;
			}
			dist[i][i] = 0;
		}
		//build edges
		for(int e=0; e<E; e++){
			scanf("%d %d %d %d", &a, &b, &m, &l);
			a--; b--;
			int cost = 0;
			for(int mo=0, hp; mo<m; mo++){
				scanf("%d", &hp);
				cost += MinMana(hp, M-1);
			}
			dist[a][b] = cost;
			dist[b][a] = cost;
			if (l > 0) reqmask[a][b] = 1<<l;
			if (l > 0) reqmask[b][a] = 1<<l;
		}
		//read coins
		for(int i=0; i<C; i++){
			scanf("%d", &coin[i]);
			coin[i]--;
		}
		//read switches
		for(int i=0; i<L; i++){
			scanf("%d", &level[i]);
			level[i]--;
		}
		if (V > MAXN){
			printf("0\n");
			continue;
		}
		//floyd warshall
		for(int k=0; k<V; k++){
			for(int i=0; i<V; i++){
				for(int j=0; j<V; j++){
					if (dist[i][j] > dist[i][k] + dist[k][j]){
						dist[i][j] = dist[i][k] + dist[k][j];
						reqmask[i][j] = reqmask[i][k] | reqmask[k][j];
					}
				}
			}
		}
		//dp
		for(int mask = (1<<V)-1; mask>=0; mask--){
			int levelmask = mask2level(mask);
			int coinmask = mask2coin(mask);
			for(int i=0; i<V; i++){
				state = INF;
				if (!(mask & (1<<i))) continue;
				if (coinmask == (1<<C)-1 && (reqmask[i][V-1] & levelmask) == reqmask[i][V-1]){
					state = dist[i][V-1];
				}
				for(int j=0; j<V; j++) {
					if ((reqmask[i][j] & levelmask) != reqmask[i][j]) continue;
					if (mask & (1<<j)) continue;
					state = min(state, dist[i][j] + dp[mask | (1<<j)][j]);
				}
			}
		}
		//ans
		printf("%d\n", dp[1][0]);
	}
	return 0;
}