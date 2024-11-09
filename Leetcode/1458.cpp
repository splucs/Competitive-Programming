#define INF 0x3f3f3f3f

class Solution {
public:
    int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size();
        vector<vector<vector<int>>> dp(2, vector<vector<int>>(m, vector<int>(2)));
        for (int i = 0; i < n; i++) {
            int ri = i&1;
            for (int j = 0; j < m; j++) {
                for (int k = 0; k < 2; k++) {
                    dp[ri][j][k] = k == 1 ? 0 : -INF;
                    if (i > 0) {
                        dp[ri][j][k] = max(dp[ri][j][k], dp[ri^1][j][k]);
                    }
                    if (j > 0) {
                        dp[ri][j][k] = max(dp[ri][j][k], dp[ri][j-1][k]);
                    }
                    int cur = nums1[i]*nums2[j];
                    if (i > 0 && j > 0) {
                        cur += dp[ri^1][j-1][1];
                    }
                    dp[ri][j][k] = max(dp[ri][j][k], cur);
                }
            }
        }
        return dp[(n-1)&1][m-1][0];
    }

};
