#define MOD 1000000007

class Solution {
public:
    int numTilings(int n) {
        int dp[3][2];
        memset(&dp, 0, sizeof dp);
        dp[1][0] = dp[0][0] = dp[1][1] = 1;
        for (int i = 2; i <= n; i++) {
            int ri = i%3, ri1 = (i-1)%3, ri2 = (i-2)%3;
            dp[ri][0] = ((dp[ri1][0] + dp[ri2][0]) % MOD + (2 * dp[ri2][1]) % MOD) % MOD;
            dp[ri][1] = (dp[ri1][1] + dp[ri1][0]) % MOD;
        }
        return dp[n%3][0];
    }
};
