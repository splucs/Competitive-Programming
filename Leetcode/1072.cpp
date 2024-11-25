class Solution {
private:
    void ensureRowIsOne(vector<vector<int>>& matrix, int row) {
        int n = matrix.size(), m = matrix[0].size();
        for (int j = 0; j < m; j++) {
            if (matrix[row][j] == 1) {
                continue;
            }
            for (int i = 0; i < n; i++) {
                matrix[i][j] = 1 - matrix[i][j];
            }
        }
    }
    int countEqualRows(vector<vector<int>>& matrix) {
        int n = matrix.size(), m = matrix[0].size();
        int ans = n;
        for (int i = 0; i < n; i++) {
            for (int j = 1; j < m; j++) {
                if (matrix[i][j] != matrix[i][0]) {
                    ans--;
                    break;
                }
            }
        }
        return ans;
    }
public:
    int maxEqualRowsAfterFlips(vector<vector<int>>& matrix) {
        int n = matrix.size(), m = matrix[0].size();
        int ans = 0;
        for (int i = 0; i < n; i++) {
            ensureRowIsOne(matrix, i);
            ans = max(ans, countEqualRows(matrix));
        }
        return ans;
    }
};
