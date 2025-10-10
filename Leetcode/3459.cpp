class Solution {
private:
    int di[4] = {1, 1, -1, -1};
    int dj[4] = {1, -1, -1, 1};
    int nxtGrid[3] = {2, 2, 0};
public:
    int lenOfVDiagonal(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        // dp[i][j][d][t] = max sequence from (i, j) going at direction d and can still do t turns.
        vector<vector<vector<vector<int>>>> dp(n,
                vector<vector<vector<int>>>(m,
                    vector<vector<int>>(4,
                        vector<int>(2))));

        int ans = 0;
        for (int t = 0; t < 2; t++) {
            for (int d = 0; d < 4; d++) {
                for (int i = di[d] > 0 ? n-1 : 0; i >= 0 && i < n; i -= di[d]) {
                    for (int j = dj[d] > 0 ? m-1 : 0; j >= 0 && j < m; j -= dj[d]) {
                        dp[i][j][d][t] = 1;
                        for (int c = 0; c < 2 && c <= t; c++) {
                            int nd = (d + c) & 3, nt = t - c;
                            int ni = i + di[nd], nj = j + dj[nd];
                            if (ni < 0 || nj < 0 || ni >= n || nj >= m) {
                                continue;
                            }
                            if (grid[ni][nj] != nxtGrid[grid[i][j]]) {
                                continue;
                            }
                            dp[i][j][d][t] = max(dp[i][j][d][t], 1 + dp[ni][nj][nd][nt]);
                        }

                        if (grid[i][j] == 1) {
                            ans = max(ans, dp[i][j][d][t]);
                        }
                    }
                }
            }
        }
        return ans;
    }
};
