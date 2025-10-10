class Solution {
public:
    int minimumArea(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        int mini = n, maxi = -1;
        int minj = m, maxj = -1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 0) {
                    continue;
                }
                mini = min(mini, i);
                maxi = max(maxi, i);
                minj = min(minj, j);
                maxj = max(maxj, j);
            }
        }
        return (maxi-mini+1) * (maxj-minj+1);
    }
};
