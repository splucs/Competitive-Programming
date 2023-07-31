class Solution {
public:
    int minimumDeleteSum(string s1, string s2) {
        int n = s1.size(), m = s2.size();
        vector<vector<int>> dp(n+1, vector<int>(m+1));
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                // Base cases
                if (i == 0 || j == 0) {
                    if (i == j) dp[i][j] = 0;
                    else if (i > 0) dp[i][j] = ((int)s1[i-1]) + dp[i-1][j];
                    else dp[i][j] = ((int)s2[j-1]) + dp[i][j-1];
                    continue;
                }

                // Recursion
                int c1 = s1[i-1], c2 = s2[j-1];
                if (c1 == c2) {
                    dp[i][j] = dp[i-1][j-1];
                } else {
                    int opt1 = c1 + dp[i-1][j];
                    int opt2 = c2 + dp[i][j-1];
                    dp[i][j] = opt1 > opt2 ? opt2 : opt1;
                }
            }
        }
        return dp[n][m];
    }
};
