class Solution {
public:
    vector<int> shortestDistanceAfterQueries(int n, vector<vector<int>>& queries) {
        vector<vector<int>> g(n);

        vector<int> dp(n);
        for (int i = 0; i < n-1; i++) {
            dp[i] = n-1-i;
            g[i].push_back(i+1);
        }
        dp[n-1] = 0;

        vector<int> ans;
        ans.reserve(n);

        for (const vector<int>& query : queries) {
            int u = query[0], v = query[1];
            g[u].push_back(v);

            for (int i = u; i >= 0; i--) {
                for (int j : g[i]) {
                    dp[i] = min(dp[i], 1 + dp[j]);
                }
            }

            ans.push_back(dp[0]);
        }
        return ans;
    }
};
