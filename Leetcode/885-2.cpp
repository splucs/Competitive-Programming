class Solution {
public:
    vector<vector<int>> spiralMatrixIII(int rows, int cols, int rStart, int cStart) {
        int di = 0, dj = 1, i = rStart, j = cStart;
        int left = rows*cols;
        vector<vector<int>> ans;
        for (int d = 1; left > 0; d++) {
            for (int dt = 0; dt < 2 && left > 0; dt++) {
                for (int it = 0, toWalk; it < d && left > 0; it += toWalk) {
                    if (i >= 0 && i < rows && j >= 0 && j < cols) {
                        left--;
                        ans.push_back({i, j});
                        toWalk = 1;
                    } else if (i < 0) {
                        toWalk = di < 1 ? d-it : -i;
                    } else if (j < 0) {
                        toWalk = dj < 1 ? d-it : -j;
                    } else if (i >= rows) {
                        toWalk = di > -1 ? d-it : i-rows+1;
                    } else if (j >= cols) {
                        toWalk = dj > -1 ? d-it : j-cols+1;
                    }
                    i += toWalk*di;
                    j += toWalk*dj;
                }
                swap(di, dj);
                dj = -dj;
            }
        }
        return ans;
    }
};
