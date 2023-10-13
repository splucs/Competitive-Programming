class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        vector<int> dp(3);
        for (int i = n-1; i >= 0; i--) {
            int &ans = dp[i%3];
            if (i+2 >= n) ans = 0;
            else ans = min(dp[(i+1)%3], dp[(i+2)%3]);
            ans += cost[i];
        }
        return min(dp[0], dp[1]);
    }
};
