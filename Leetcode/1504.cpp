class Solution {
public:
    int numSubmat(vector<vector<int>>& mat) {
        int n = mat.size(), m = mat[0].size();
        vector<vector<int>> lastZeroInRow(n, vector<int>(m));
        for (int i = 0; i < n; i++) {
            int last = -1;
            for (int j = 0; j < m; j++) {
                if (mat[i][j] == 0) {
                    last = j;
                }
                lastZeroInRow[i][j] = last;
            }
        }

        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int cur = j+1;
                for (int it = i; it >= 0 && cur > 0; it--) {
                    cur = min(cur, j-lastZeroInRow[it][j]);
                    ans += cur;
                }
            }
        }
        return ans;
    }
};
