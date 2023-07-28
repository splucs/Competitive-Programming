class Solution {
public:
    bool PredictTheWinner(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp[2];
        dp[0] = nums;
        dp[1].resize(n);
        for (int len = 1; len < n; len++) {
            int rlen = len&1;
            for (int i = 0; i+len < n; i++) {
                int j = i + len;
                int opt1 = nums[i] - dp[rlen^1][i+1];
                int opt2 = nums[j] - dp[rlen^1][i];
                dp[rlen][i] = opt1 > opt2 ? opt1 : opt2;
            }
        }
        return dp[(n^1)&1][0] >= 0;
    }
};
