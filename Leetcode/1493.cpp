class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int n = nums.size();
        int m = 2;

        // dp[i][j] = longest sub-array of 1's that end in i given I can remove j elements
        int dp[2][2];
        memset(&dp, 0, sizeof dp);

        int ans = 0;
        for(int i = 0; i < n; i++) {
            int ri = i&1;
            for (int j = 0; j < m; j++) {
                int &cur = dp[ri][j];
                if (nums[i] == 1) {
                    cur = 1;
                    if (i > 0) cur += dp[ri^1][j];
                } else {
                    cur = 0;
                    if (i > 0 && j > 0) cur += dp[ri^1][j-1];
                }
            }
            int cur = dp[ri][1];
            ans = ans > cur ? ans : cur;
        }

        if (ans == n) ans--;
        return ans;
    }
};
