class Solution {
public:
    int countNegatives(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int ans = 0;
        for (int i = m-1, j = 0; i >= 0; i--) {
            for (int dj = 64; dj; dj >>= 1) {
                if (j+dj >= n) continue;
                if (grid[i][j+dj] >= 0) j += dj;
            }
            if (j < n && grid[i][j] >= 0) j++;
            ans += n-j;
        }
        return ans;
    }
};
