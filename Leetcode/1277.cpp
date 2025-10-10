class Solution {
public:
    int countSquares(vector<vector<int>>& matrix) {
        int n = matrix.size(), m = matrix[0].size();
        vector<vector<int>> lastZeroInRow(n, vector<int>(m));
        for (int i = 0; i < n; i++) {
            int last = -1;
            for (int j = 0; j < m; j++) {
                if (matrix[i][j] == 0) {
                    last = j;
                }
                lastZeroInRow[i][j] = last;
            }
        }

        vector<vector<int>> lastZeroInCol(n, vector<int>(m));
        for (int j = 0; j < m; j++) {
            int last = -1;
            for (int i = 0; i < n; i++) {
                if (matrix[i][j] == 0) {
                    last = i;
                }
                lastZeroInCol[i][j] = last;
            }
        }

        vector<vector<int>> biggestSquare(n, vector<int>(m, 0));
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int last = -1;
            for (int j = 0; j < m; j++) {
                if (matrix[i][j] == 0) {
                    continue;
                }
                biggestSquare[i][j] = min(j - lastZeroInRow[i][j], i - lastZeroInCol[i][j]);
                if (i > 0 && j > 0) {
                    biggestSquare[i][j] = min(biggestSquare[i][j], 1 + biggestSquare[i-1][j-1]);
                }
                ans += biggestSquare[i][j];
            }
        }
        return ans;
    }
};
