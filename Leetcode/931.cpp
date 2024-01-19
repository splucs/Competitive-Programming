#define INF 0x3f3f3f3f

class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        vector<vector<int>> dp(2, vector<int>(m));
        for (int i = 0; i < n; i++) {
            int ri = i&1;
            for (int j = 0; j < m; j++) {
                dp[ri][j] = matrix[i][j];
                if (i > 0) {
                    int extra = INF;
                    for (int pj = j > 0 ? j-1 : 0; pj < m && pj <= j+1; pj++) {
                        extra = min(extra, dp[ri^1][pj]);
                    }
                    dp[ri][j] += extra;
                }
            }
        }
        int ans = INF;
        int ri = (n-1)&1;
        for (int j = 0; j < m; j++) {
            ans = min(ans, dp[ri][j]);
        }
        return ans;
    }
};
