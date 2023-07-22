class Solution {
private:
    int di[8] = {1, 1, 2, 2, -1, -1, -2, -2};
    int dj[8] = {2, -2, 1, -1, 2, -2, 1, -1};
public:
    double knightProbability(int n, int k, int row, int column) {
        vector<vector<double>> prob[2];
        for (int kt = 0; kt <= k; kt++) {
            prob[kt&1] = vector<vector<double>>(n, vector<double>(n, 0));
            if (kt == 0) {
                prob[0][row][column] = 1;
                continue;
            }

            for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
                for (int d = 0; d < 8; d++) {
                    int ni = i + di[d];
                    int nj = j + dj[d];
                    if (ni < 0 || nj < 0 || ni >= n || nj >= n) {
                        continue;
                    }
                    prob[kt&1][ni][nj] += prob[(kt^1)&1][i][j]/8.0;
                }
            }
        }
        double ans = 0.0;
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
            ans += prob[k&1][i][j];
        }
        return ans;
    }
};
