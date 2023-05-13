class Solution {
public:
    int MOD = 1e9+7;
    int countGoodStrings(int low, int high, int zero, int one) {
        int n = max(low, high);
        vector<int> dp(n+1, 0);
        dp[0] = 1;
        for (int i = 1; i <= n; i++) {
            if (i >= zero) dp[i] = (dp[i] + dp[i-zero])%MOD;
            if (i >= one) dp[i] = (dp[i] + dp[i-one])%MOD;
        }
        int ans = 0;
        for (int i = low; i <= high; i++) {
            ans = (ans + dp[i])%MOD;
        }
        return ans;
    }
};
