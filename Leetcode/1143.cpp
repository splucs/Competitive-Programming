class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int n = text1.size(), m = text2.size();
        vector<vector<int>> dp(n, vector<int>(m));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int &ans = dp[i][j];

                ans = text1[i] == text2[j] ? 1 : 0;
                if (i > 0 && j > 0) {
                    ans += dp[i-1][j-1];
                }

                if (i > 0) {
                    ans = max(ans, dp[i-1][j]);
                }
                if (j > 0) {
                    ans = max(ans, dp[i][j-1]);
                }
            }
        }

        return dp[n-1][m-1];
    }
};

