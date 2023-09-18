class Solution {
public:
    vector<int> kWeakestRows(vector<vector<int>>& mat, int k) {
        int n = mat.size();
        int m = mat[0].size();
        vector<vector<int>> byStrength(m+1);
        for (int i = 0; i < n; i++) {
            int j = 0;
            while (j < m && mat[i][j] == 1) j++;
            byStrength[j].push_back(i);
        }
        vector<int> ans;
        for (int j = 0; j <= m; j++) {
            if (ans.size() == k) break;
            for (int i : byStrength[j]) {
                if (ans.size() == k) break;
                ans.push_back(i);
            }
        }
        return ans;
    }
};
