class Solution {
public:
    bool PredictTheWinner(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(n));
        for (int i = n-1; i >= 0; i--) {
            dp[i][i] = nums[i];
            for (int len = 1; i+len < n; len++) {
                int j = i + len;
                int opt1 = nums[i] - dp[i+1][j];
                int opt2 = nums[j] - dp[i][j-1];
                dp[i][j] = opt1 > opt2 ? opt1 : opt2;
            }
        }
        return dp[0][n-1] >= 0;
    }
};
