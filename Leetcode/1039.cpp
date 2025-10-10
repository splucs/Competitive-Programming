#define INF 0x3f3f3f3f
class Solution {
public:
    int minScoreTriangulation(vector<int>& values) {
        int n = values.size();
        vector<vector<int>> dp(n, vector<int>(n, INF));

        for (int len = 1; len < n; len++) {
            for (int l = 0; l+len < n; l++) {
                int r = l+len;
                if (len == 1) {
                    dp[l][r] = 0;
                    continue;
                }
                for (int i = l+1; i < r; i++) {
                    dp[l][r] = min(dp[l][r], values[l]*values[r]*values[i] + dp[l][i] + dp[i][r]);
                }
            }
        }
        return dp[0][n-1];
    }
};
