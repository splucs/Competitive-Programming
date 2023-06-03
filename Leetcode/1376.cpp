class Solution {
public:
    int numOfMinutes(int n, int headID, vector<int>& manager, vector<int>& informTime) {
        vector<vector<int>> g(n);
        for (int u = 0; u < n; u++) {
            int v = manager[u];
            if (v == -1) continue;
            g[v].push_back(u);
        }
        return dfs(headID, informTime, g);
    }
    int dfs(int u, vector<int> &informTime, vector<vector<int>> &g) {
        if (g[u].size() == 0) {
            return 0;
        }
        int ans = 0;
        for (int v : g[u]) {
            ans = max(ans, dfs(v, informTime, g));
        }
        return ans + informTime[u];
    }
};
