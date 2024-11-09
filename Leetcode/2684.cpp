class Solution {
public:
    int maxMoves(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<bool>> dp(n, vector<bool>(m, false));
        for (int i = 0; i < n; i++) {
            dp[i][0] = true;
        }
        int ans = 0;
        for (int j = 1; j < m; j++) {
            for (int i = 0; i < n; i++) {
                for (int it = i > 0 ? i-1 : i; !dp[i][j] && it < n && it <= i+1; it++) {
                    if (grid[it][j-1] < grid[i][j]) {
                        dp[i][j] = dp[it][j-1];
                    }
                }
                if (dp[i][j]) {
                    ans = max(ans, j);
                }
            }
        }
        return ans;
    }
};
