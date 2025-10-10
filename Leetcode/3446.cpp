class Solution {
public:
    vector<vector<int>> sortMatrix(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<int> diag(n);
        for (int diff = -n+1; diff <= n-1; diff++) {
            diag.clear();
            for (int i = max(0, diff); i < n && i-diff < n; i++) {
                int j = i-diff;
                diag.push_back(grid[i][j]);
            }
            if (diff >= 0) {
                sort(diag.rbegin(), diag.rend());
            } else {
                sort(diag.begin(), diag.end());
            }
            for (int i = max(0, diff), it = 0; i < n && i-diff < n; i++, it++) {
                int j = i-diff;
                grid[i][j] = diag[it];
            }
        }
        return grid;
    }
};
