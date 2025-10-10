class Solution {
public:
    int maxSum(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        int ans = 0;
        for (int i = 2; i < n; i++) {
            for (int j = 2; j < m; j++) {
                ans = max(ans,
                        grid[i][j] + grid[i][j-1] + grid[i][j-2]
                                    + grid[i-1][j-1]
                        + grid[i-2][j] + grid[i-2][j-1] + grid[i-2][j-2]);
            }
        }
        return ans;
    }
};
