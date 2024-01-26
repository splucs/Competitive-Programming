#define MOD 1000000007
class Solution {
private:
    int di[4] = {0, 1, 0, -1};
    int dj[4] = {1, 0, -1, 0};
public:
    int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
        vector<vector<vector<int>>> dp(2, vector<vector<int>>(m, vector<int>(n, 0)));
        for (int t = 1; t <= maxMove; t++) {
            int rt = t&1;
            for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) {
                dp[rt][i][j] = 0;
                for (int dir = 0; dir < 4; dir++) {
                    int ni = i + di[dir];
                    int nj = j + dj[dir];
                    if (ni < 0 || ni >= m || nj < 0 || nj >= n) {
                        dp[rt][i][j] = (dp[rt][i][j] + 1) % MOD;
                    } else {
                        dp[rt][i][j] = (dp[rt][i][j] + dp[rt^1][ni][nj]) % MOD;
                    }
                }
            }
        }
        return dp[maxMove&1][startRow][startColumn];
    }
};
