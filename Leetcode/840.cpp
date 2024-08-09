const int ALL_FLAGS = (1<<10)-2;

class Solution {
public:
    int numMagicSquaresInside(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> rowMask(n, vector<int>(m, 0));
        vector<vector<int>> rowSum(n, vector<int>(m, 0));
        vector<vector<int>> colSum(n, vector<int>(m, 0));
        vector<vector<int>> diagSum(n, vector<int>(m, 0));
        vector<vector<int>> secDiagSum(n, vector<int>(m, 0));
        int ans = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                rowMask[i][j] = (1 << grid[i][j]);
                if (j > 0) rowMask[i][j] ^= rowMask[i][j-1];
                if (j > 2) rowMask[i][j] ^= (1 << grid[i][j-3]);

                rowSum[i][j] = grid[i][j];
                if (j > 0) rowSum[i][j] += rowSum[i][j-1];
                if (j > 2) rowSum[i][j] -= grid[i][j-3];

                colSum[i][j] = grid[i][j];
                if (i > 0) colSum[i][j] += colSum[i-1][j];
                if (i > 2) colSum[i][j] -= grid[i-3][j];

                diagSum[i][j] = grid[i][j];
                if (i > 0 && j > 0) diagSum[i][j] += diagSum[i-1][j-1];
                if (i > 2 && j > 2) diagSum[i][j] -= grid[i-3][j-3];

                secDiagSum[i][j] = grid[i][j];
                if (i > 0 && j+1 < m) secDiagSum[i][j] += secDiagSum[i-1][j+1];
                if (i > 2 && j+3 < m) secDiagSum[i][j] -= grid[i-3][j+3];

                if (i >= 2 && j >= 2
                    && (rowMask[i][j] ^ rowMask[i-1][j] ^ rowMask[i-2][j]) == ALL_FLAGS
                    && rowSum[i][j] == 15 && rowSum[i-1][j] == 15 && rowSum[i-2][j] == 15
                    && colSum[i][j] == 15 && colSum[i][j-1] == 15 && colSum[i][j-2] == 15
                    && diagSum[i][j] == 15 && secDiagSum[i][j-2] == 15) {
                    ans++;
                }
            }
        }

        return ans;
    }
};
