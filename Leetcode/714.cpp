class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size();
        int dp[2][2];
        memset(&dp, 0, sizeof dp);
        
        for (int i = n-1; i >= 0; i--) {
            int r = i&1, opt1, opt2;

            opt1 = dp[r^1][1];
            opt2 = dp[r^1][0]+prices[i];
            dp[r][1] = opt1 > opt2 ? opt1 : opt2;

            opt1 = dp[r^1][0];
            opt2 = dp[r^1][1]-prices[i]-fee;
            dp[r][0] = opt1 > opt2 ? opt1 : opt2;
        }
        return dp[0][0];
    }
};
