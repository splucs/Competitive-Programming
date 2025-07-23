class Solution {
private:
    int di[4] = {0, 1, 0, -1};
    int dj[4] = {1, 0, -1, 0};
    int n, m;
    vector<vector<int>> grid;
    int dfs(int i, int j) {
        if (grid[i][j] == 0) {
            return 0;
        }
        int ans = grid[i][j];
        grid[i][j] = 0;
        for (int dir = 0; dir < 4; dir++) {
            int ni = i + di[dir];
            int nj = j + dj[dir];
            if (ni < 0 || nj < 0 || ni >= n || nj >= m) {
                continue;
            }
            ans += dfs(ni, nj);
        }
        return ans;
    }
public:
    int findMaxFish(vector<vector<int>>& _grid) {
        grid.swap(_grid);
        n = grid.size();
        m = grid[0].size();

        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                ans = max(ans, dfs(i, j));
            }
        }
        return ans;
    }
};
