class Solution {
private:
    vector<vector<int>> g[2];
    int countUpTo(int t, int u, int p, int dist) {
        if (dist == 0) {
            return 1;
        }
        int ans = 1;
        for (int v : g[t][u]) {
            if (v == p) {
                continue;
            }
            ans += countUpTo(t, v, u, dist-1);
        }
        return ans;
    }
public:
    vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2, int k) {
        int n = edges1.size() + 1;
        int m = edges2.size() + 1;
        g[0].resize(n);
        g[1].resize(m);
        for (const vector<int>& edge : edges1) {
            int u = edge[0], v = edge[1];
            g[0][u].push_back(v);
            g[0][v].push_back(u);
        }
        for (const vector<int>& edge : edges2) {
            int u = edge[0], v = edge[1];
            g[1][u].push_back(v);
            g[1][v].push_back(u);
        }
        int max2 = 0;
        if (k > 0) {
            for (int u = 0; u < m; u++) {
                max2 = max(max2, countUpTo(1, u, -1, k-1));
            }
        }
        vector<int> ans(n);
        for (int u = 0; u < n; u++) {
            ans[u] = countUpTo(0, u, -1, k) + max2;
        }
        return ans;
    }
};
