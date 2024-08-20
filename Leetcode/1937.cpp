class Solution {
public:
    long long maxPoints(vector<vector<int>>& points) {
        int n = points.size();
        int m = points[0].size();
        vector<long long> dp(m, 0), up(m), down(m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                up[j] = max(dp[j] + j, j > 0 ? up[j-1] : 0);
            }
            for (int j = m-1; j >= 0; j--) {
                down[j] = max(dp[j] + m-1-j, j+1 < m ? down[j+1] : 0);
            }

            for (int j = 0; j < m; j++) {
                dp[j] = max(up[j]-j, down[j]-(m-1-j)) + points[i][j];
            }
        }
        long long ans = 0;
        for (int j = 0; j < m; j++) {
            ans = max(ans, dp[j]);
        }
        return ans;
    }
};
