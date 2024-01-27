#define MOD 1000000007

class Solution {
public:
    int kInversePairs(int n, int k) {
        // Definitions:
        // dp[n][k] = dp[n-1][k] + dp[n-1][k-1] + ... + dp[n-1][k-n+1]
        // P[n][k] = dp[n][k] + dp[n][k-1] + ... + dp[n][0]

        // Recursions:
        // P[n][0] = dp[n][0] = 1
        // P[n][<0] = 0
        // P[n][k] = dp[n][k] + P[n][k-1]
        // dp[n][k] = P[n-1][k] - P[n-1][k-n]

        vector<vector<int>> P(2, vector<int>(k+1, 1));
        for (int i = 2; i <= n; i++) {
            int ri = i&1;
            for (int j = 0; j <= k; j++) {
                int dp = 0;
                dp = P[ri^1][j];
                if (j >= i) {
                    dp = (dp - P[ri^1][j-i] + MOD) % MOD;
                }

                int &ans = P[ri][j];
                ans = dp;
                if (j > 0) {
                    ans = (ans + P[ri][j-1]) % MOD;
                }
            }
        }

        int ans = P[n&1][k];
        if (k > 0) {
            ans = (ans - P[n&1][k-1] + MOD) % MOD;
        }
        return ans;
    }
};
