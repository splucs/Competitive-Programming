
class Solution {
private:
    const int MAX = 2000000000;
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int n = obstacleGrid.size();
        int m = obstacleGrid[0].size();
        vector<unsigned int> dp(m, 0);
        dp[m-1] = 1;
        for (int i = n-1; i >= 0; i--) {
            for (int j = m-1; j >= 0; j--) {
                if (obstacleGrid[i][j]) {
                    dp[j] = 0;
                } else if (j+1 < m) {
                    dp[j] += dp[j+1];
                    if (dp[j] > MAX) dp[j] = 0;
                }
            }
        }
        return dp[0];
    }
};
