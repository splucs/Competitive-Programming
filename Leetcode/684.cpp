class Solution {
private:
    int n, cnt, ans;
    vector<int> viz;
    vector<vector<pair<int, int>>> g;
    void dfs(int u, int from) {
        viz[u] = ++cnt;
        for (pair<int, int> e : g[u]) {
            int v = e.first, i = e.second;
            if (v == from) {
                continue;
            }
            if (viz[v] == 0) {
                dfs(v, u);
            }
            if (viz[v] <= viz[u]) {
                ans = max(ans, i);
                viz[u] = viz[v];
            }
        }
    }
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        n = edges.size(), cnt = 0, ans = 0;
        g.resize(n+1);
        viz.assign(n+1, 0);
        for (int i = 0; i < n; i++) {
            int u = edges[i][0], v = edges[i][1];
            g[u].push_back(make_pair(v, i));
            g[v].push_back(make_pair(u, i));
        }
        dfs(1, -1);
        return edges[ans];
    }
};
