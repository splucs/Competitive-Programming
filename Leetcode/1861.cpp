class Solution {
private:
    void fall(vector<vector<char>>& ans, int j, int i1, int i2, int numStones) {
        for (int i = i2; i >= i1; i--) {
            if (numStones > 0) {
                ans[i][j] = '#';
                numStones--;
            } else {
                ans[i][j] = '.';
            }
        }
    }
public:
    vector<vector<char>> rotateTheBox(vector<vector<char>>& box) {
        int m = box.size(), n = box[0].size();
        vector<vector<char>> ans(n, vector<char>(m));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                ans[i][m-j-1] = box[j][i];
            }
        }

        for (int j = 0; j < m; j++) {
            int lastObs = -1, numStones = 0;
            for (int i = 0; i < n; i++) {
                if (ans[i][j] == '#') {
                    numStones++;
                }
                if (ans[i][j] == '*') {
                    fall(ans, j, lastObs+1, i-1, numStones);
                    numStones = 0;
                    lastObs = i;
                }
            }
            fall(ans, j, lastObs+1, n-1, numStones);
        }
        return ans;
    }
};
