#define MOD 1000000007
class Solution {
public:
    int numberOfWays(int n, int x) {
        vector<int> dp(n+1, 0);

        dp[0] = 1;
        for (int j = 1; j <= n; j++) {
            long long pj = 1;
            for (int xt = 0; xt < x; xt++) {
                pj *= j;
            }
            for (int i = n; i >= pj; i--) {
                dp[i] = (dp[i] + dp[i-pj]) % MOD;
            }
        }

        return dp[n];
    }
};
