#define MOD 1000000007
class Solution {
public:
    int peopleAwareOfSecret(int n, int delay, int forget) {
        vector<int> dp(n+1, 0);
        dp[1] = 1;
        for (int i = 2; i <= n; i++) {
            if (i > delay) {
                dp[i] = (dp[i] + dp[i-delay]) % MOD;
            }
            if (i > forget) {
                dp[i] = (dp[i] - dp[i-forget] + MOD) % MOD;
            }
            dp[i] = (dp[i] + dp[i-1]) % MOD;
        }
        return (dp[n] - dp[n-forget] + MOD) % MOD;
    }
};
