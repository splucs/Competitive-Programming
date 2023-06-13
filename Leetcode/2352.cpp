class Solution {
public:
    int equalPairs(vector<vector<int>>& grid) {
        int n = grid.size();
        map<vector<int>, int> rows, cols;
        for (vector<int> &row : grid) {
            rows[row]++;
        }
        for (int j = 0; j < n; j++) {
            vector<int> col(n);
            for (int i = 0; i < n; i++) {
                col[i] = grid[i][j];
            }
            cols[col]++;
        }
        int ans = 0;
        for (pair<vector<int>, int> rowEntry : rows) {
            vector<int> &row = rowEntry.first;
            int rowCount = rowEntry.second;
            int colCount = cols[row];
            ans += rowCount*colCount;
        }
        return ans;
    }
};
