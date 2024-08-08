class Solution {
public:
    vector<vector<int>> spiralMatrixIII(int rows, int cols, int rStart, int cStart) {
        int di = 0, dj = 1, i = rStart, j = cStart;
        int left = rows*cols;
        vector<vector<int>> ans;
        for (int d = 1; left > 0; d++) {
            for (int dt = 0; dt < 2 && left > 0; dt++) {
                for (int it = 0; it < d && left > 0; it++) {
                    if (i >= 0 && i < rows && j >= 0 && j < cols) {
                        left--;
                        ans.push_back({i, j});
                    }
                    i += di;
                    j += dj;
                }
                swap(di, dj);
                dj = -dj;
            }
        }
        return ans;
    }
};
