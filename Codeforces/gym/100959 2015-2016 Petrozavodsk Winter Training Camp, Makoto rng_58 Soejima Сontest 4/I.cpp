#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define INF (1LL<<60)

typedef long long ll;
map<ll, vector<int> > idx, idy;
int N, invx[MAXN], invy[MAXN];
ll x[MAXN], y[MAXN];
char dir[MAXN];
ll dist[MAXN];

int dijkstra() {
	for(int i=0; i<N; i++) dist[i] = INF;
	dist[0]=0;
	set<pair<ll, int> > nodes;
	nodes.insert(make_pair(0LL, 0));
	while(!nodes.empty()){
		int u = nodes.begin()->second;
		nodes.erase(nodes.begin());
		if (dir[u] == 'U' || dir[u] == 'D'){
            vector<int> & vet = idx[x[u]];
            if (dir[u] == 'U'){
                for(int i = invx[u]+1; i<(int)vet.size(); i++){
                    int v = vet[i];
                    if (dist[v] > dist[u] + abs(y[u] - y[v])){
                        nodes.erase(make_pair(dist[v], v));
                        dist[v] = dist[u] + abs(y[u] - y[v]);
                        if(dir[u] != dir[v]) nodes.insert(make_pair(dist[v], v));
                    }
                    else if (dir[v] == dir[u]) break;
                }
            }
            if (dir[u] == 'D'){
                for(int i = invx[u]-1; i>=0; i--){
                    int v = vet[i];
                    if (dist[v] > dist[u] + abs(y[u] - y[v])){
                        nodes.erase(make_pair(dist[v], v));
                        dist[v] = dist[u] + abs(y[u] - y[v]);
                        if(dir[u] != dir[v]) nodes.insert(make_pair(dist[v], v));
                    }
                    else if (dir[v] == dir[u]) break;
                }
            }
		}
		if (dir[u] == 'L' || dir[u] == 'R'){
            vector<int> & vet = idy[y[u]];
            if (dir[u] == 'R'){
                for(int i = invy[u]+1; i<(int)vet.size(); i++){
                    int v = vet[i];
                    if (dist[v] > dist[u] + abs(x[u] - x[v])){
                        nodes.erase(make_pair(dist[v], v));
                        dist[v] = dist[u] + abs(x[u] - x[v]);
                        if(dir[u] != dir[v]) nodes.insert(make_pair(dist[v], v));
                    }
                    else if (dir[v] == dir[u]) break;
                }
            }
            if (dir[u] == 'L'){
                for(int i = invy[u]-1; i>=0; i--){
                    int v = vet[i];
                    if (dist[v] > dist[u] + abs(x[u] - x[v])){
                        nodes.erase(make_pair(dist[v], v));
                        dist[v] = dist[u] + abs(x[u] - x[v]);
                        if(dir[u] != dir[v]) nodes.insert(make_pair(dist[v], v));
                    }
                    else if (dir[v] == dir[u]) break;
                }
            }
		}
	}
}

bool compx(int i, int j) {
    if (x[i] == x[j]) return y[i] < y[j];
    return x[i] < x[j];
}

bool compy(int i, int j) {
    if (y[i] == y[j]) return x[i] < x[j];
    return y[i] < y[j];
}

int main() {
    ll T;
    scanf("%d %I64d", &N, &T);
    for(int i=0; i<N; i++) {
        scanf("%I64d %I64d %c", &x[i], &y[i], &dir[i]);
        idx[x[i]].push_back(i);
        idy[y[i]].push_back(i);
    }
    for(map<ll, vector<int> >::iterator it = idx.begin(); it!=idx.end(); it++){
        sort(it->second.begin(), it->second.end(), &compy);
        for(int i=0; i<(int)it->second.size(); i++){
            invx[it->second[i]] = i;
        }
    }
    for(map<ll, vector<int> >::iterator it = idy.begin(); it!=idy.end(); it++){
        sort(it->second.begin(), it->second.end(), &compx);
        for(int i=0; i<(int)it->second.size(); i++){
            invy[it->second[i]] = i;
        }
    }
    dijkstra();
    for(int i=0; i<N; i++){
        if (dist[i] < INF){
            if (dir[i] == 'U') y[i] += max(0LL, T-dist[i]);
            if (dir[i] == 'D') y[i] -= max(0LL, T-dist[i]);
            if (dir[i] == 'R') x[i] += max(0LL, T-dist[i]);
            if (dir[i] == 'L') x[i] -= max(0LL, T-dist[i]);
        }
        printf("%I64d %I64d\n", x[i], y[i]);
    }
    return 0;
}