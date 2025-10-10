class Solution {
public:
    int maxCollectedFruits(vector<vector<int>>& fruits) {
        int n = fruits.size();
        vector<vector<int>> dp(2, vector<int>(n, 0));

        // solve for child (0.0)
        int ans = 0;
        for (int i = 0; i < n; i++) {
            ans += fruits[i][i];
            fruits[i][i] = 0;
        }

        // solve for child (0, n-1)
        dp[(n-1)&1][n-1] = 0;
        for (int i = n-2; i >= 0; i--) {
            int ri = i&1;
            for (int j = n-1; j >= i; j--) {
                dp[ri][j] = 0;
                for (int nj = max(j-1, i+1); nj <= min(j+1, n-1); nj++) {
                    dp[ri][j] = max(dp[ri][j], dp[ri^1][nj]);
                }
                dp[ri][j] += fruits[i][j];
            }
        }
        ans += dp[0][n-1];

        // solve for child (n-1, 0)
        dp[(n-1)&1][n-1] = 0;
        for (int j = n-2; j >= 0; j--) {
            int rj = j&1;
            for (int i = n-1; i >= j; i--) {
                dp[rj][i] = 0;
                for (int ni = max(i-1, j+1); ni <= min(i+1, n-1); ni++) {
                    dp[rj][i] = max(dp[rj][i], dp[rj^1][ni]);
                }
                dp[rj][i] += fruits[i][j];
            }
        }
        ans += dp[0][n-1];

        return ans;
    }
};
