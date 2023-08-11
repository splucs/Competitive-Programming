class Solution {
public:
    int change(int amount, vector<int>& coins) {
        int n = coins.size();
        vector<int> dp(amount+1, 0);
        dp[0] = 1;
        for (int j = 0; j < n; j++) {
            int coin = coins[j];
            for (int i = coin; i <= amount; i++) {
                dp[i] += dp[i-coin];
            }
        }
        return dp[amount];
    }
};
