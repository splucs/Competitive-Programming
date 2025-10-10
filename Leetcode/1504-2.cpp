class Solution {
public:
    int numSubmat(vector<vector<int>>& mat) {
        int n = mat.size(), m = mat[0].size();
        vector<vector<int>> lastZeroInCol(n, vector<int>(m));
        for (int j = 0; j < m; j++) {
            int last = -1;
            for (int i = 0; i < n; i++) {
                if (mat[i][j] == 0) {
                    last = i;
                }
                lastZeroInCol[i][j] = last;
            }
        }

        int ans = 0;
        vector<int> lastZero(n), cnt(n);
        for (int i = 0; i < n; i++) {
            lastZero.clear(); cnt.clear();
            int lastZeroSum = 0, cntSum = 0;
            for (int j = 0; j < m; j++) {
                int curCnt = i - lastZeroInCol[i][j];
                while (curCnt < cntSum) {
                    int cntToRemove = min(cntSum - curCnt, cnt.back());
                    cnt.back() -= cntToRemove;
                    cntSum -= cntToRemove;
                    lastZeroSum -= cntToRemove * lastZero.back();
                    if (cnt.back() == 0) {
                        cnt.pop_back();
                        lastZero.pop_back();
                    }
                }
                if (curCnt > cntSum) {
                    lastZero.push_back(j-1);
                    cnt.push_back(curCnt - cntSum);
                    lastZeroSum += lastZero.back() * cnt.back();
                    cntSum = curCnt;
                }
                ans += curCnt*j - lastZeroSum;
            }
        }
        return ans;
    }
};
