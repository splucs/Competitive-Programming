class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
        int n = mat.size(), m = mat[0].size();
        vector<int> ans;
        for (int sum = 0; sum < n+m-1; sum++) {
            if (sum & 1) {
                for (int i = max(0, sum-m+1); i <= sum && i < n; i++) {
                    ans.push_back(mat[i][sum-i]);
                }
            } else {
                for (int j = max(0, sum-n+1); j <= sum && j < m; j++) {
                    ans.push_back(mat[sum-j][j]);
                }
            }
        }
        return ans;
    }
};
