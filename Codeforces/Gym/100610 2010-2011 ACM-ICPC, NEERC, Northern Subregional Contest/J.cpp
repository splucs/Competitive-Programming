#include <bits/stdc++.h>
using namespace std;
#define MAXN 2009
#define INF (1ll<<60)

typedef long long ll;
typedef pair<ll, int> ii;

void dijktra(vector<ii> *adj, ll* dist, int s) {
    for(int i=0; i<MAXN; i++) {
        dist[i] = INF;
    }
    dist[s] = 0;
    set<ii> pq;
    pq.insert(ii(dist[s], s));
    while(!pq.empty()) {
        int u = pq.begin()->second;
        pq.erase(pq.begin());
        for(int i=0; i<(int)adj[u].size(); i++) {
            ll w = adj[u][i].first;
            int v = adj[u][i].second;
            if (dist[v] > dist[u] + w){
                if(pq.count(ii(dist[v], v))) pq.erase(ii(dist[v], v));
                dist[v] = dist[u] + w;
                pq.insert(ii(dist[v], v));
            }
        }
    }
}

vector<ii> adj1[MAXN], adj2[MAXN], adj[MAXN];
ll dist1[MAXN], dist2[MAXN];
int n, s, t, m, inv[MAXN];
bool num[MAXN], vis[MAXN];
vector<int> tops;

bool ts(int u){
    if (vis[u]) return true;
    vis[u] = true;
    num[u] = true;
    for(int i=0; i<(int)adj[u].size(); i++){
        int v = adj[u][i].second;
        if (num[v]) return false;
        if (!ts(v)) return false;
    }
    inv[u] = tops.size();
    tops.push_back(u);
    num[u] = false;
    return true;
}

ll dp[MAXN];

int main() {
    freopen("journey.in", "r", stdin);
    freopen("journey.out", "w", stdout);

    int u, v;
    ll w;
    scanf("%d %d %d", &n, &s, &t);
    scanf("%d", &m);
    while(m-->0){
        scanf("%d %d %I64d", &u, &v, &w);
        adj1[u].push_back(ii(w, v));
        adj1[v].push_back(ii(w, u));
    }
    dijktra(adj1, dist1, t);
    scanf("%d", &m);
    while(m-->0){
        scanf("%d %d %I64d", &u, &v, &w);
        adj2[u].push_back(ii(w, v));
        adj2[v].push_back(ii(w, u));
    }
    dijktra(adj2, dist2, t);
    for(u=1; u<=n; u++){
        num[u] = vis[u] = false;
        for(int i=0; i<(int)adj1[u].size(); i++) {
            ll w = adj1[u][i].first;
            int v = adj1[u][i].second;
            if (dist1[v] < dist1[u]){
                adj[u].push_back(ii(w, v+n));
            }
        }
    }
    for(u=1; u<=n; u++){
        num[u+n] = vis[u+n] = false;
        for(int i=0; i<(int)adj2[u].size(); i++) {
            ll w = adj2[u][i].first;
            int v = adj2[u][i].second;
            if (dist2[v] < dist2[u]){
                adj[u+n].push_back(ii(w, v));
            }
        }
    }
    if (!ts(s)){
        printf("-1\n");
        fclose(stdin);
        fclose(stdout);
        return 0;
    }

    for(int i=0; i<(int)tops.size(); i++){
        u = tops[i];
        dp[i] = 0;
        for(int j=0; j<(int)adj[u].size(); j++) {
            v = adj[u][j].second;
            w = adj[u][j].first;
            dp[i] = max(dp[i], dp[inv[v]] + w);
        }
    }

    printf("%I64d\n", dp[inv[s]]);

	fclose(stdin);
	fclose(stdout);
	return 0;
}