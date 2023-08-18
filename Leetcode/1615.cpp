class Solution {
public:
    int maximalNetworkRank(int n, vector<vector<int>>& roads) {
        vector<vector<int>> g(n, vector<int>(n, 0));
        vector<int> rank(n, 0);
        for (vector<int>& road : roads) {
            int u = road[0];
            int v = road[1];
            g[u][v]++;
            g[v][u]++;
            rank[u]++;
            rank[v]++;
        }
        int ans = 0;
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < u; v++) {
                int cur = rank[u] + rank[v] - g[u][v];
                ans = cur > ans ? cur : ans;
            }
        }
        return ans;
    }
};
