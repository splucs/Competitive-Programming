class Solution {
private:
    vector<vector<int>> g;
    vector<bool> hasApple;
    int ans = 0;

    bool dfs(int u, int comingFrom) {
        for (int v : g[u]) {
            if (v == comingFrom) {
                continue;
            }
            if (dfs(v, u)) {
                hasApple[u] = true;
                ans += 2;
            }
        }
        return hasApple[u];
    }
public:
    int minTime(int n, vector<vector<int>>& edges, vector<bool>& _hasApple) {
        g.resize(n);
        for (const vector<int>& e : edges) {
            int u = e[0], v = e[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }
        hasApple.swap(_hasApple);

        dfs(0, -1);
        return ans;
    }
};
