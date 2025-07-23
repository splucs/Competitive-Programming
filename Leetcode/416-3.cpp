class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for (int num : nums) {
            sum += num;
        }
        if (sum & 1) {
            return false;
        }
        sum >>= 1;

        int n = nums.size();
        vector<vector<bool>> dp(n+1, vector<bool>(sum+1, false));
        dp[n][0] = true;
        for (int i = n-1; i >= 0; i--) {
            for (int bal = 0; bal <= sum; bal++) {
                dp[i][bal] = dp[i+1][bal];
                if (bal >= nums[i]) {
                    dp[i][bal] = dp[i][bal] || dp[i+1][bal-nums[i]];
                }
            }
        }
        return dp[0][sum];
    }
};
