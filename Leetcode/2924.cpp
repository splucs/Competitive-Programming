class Solution {
public:
    int findChampion(int n, vector<vector<int>>& edges) {
        vector<int> degree(n, 0);
        for (const vector<int>& edge : edges) {
            degree[edge[1]]++;
        }
        int ans = -1;
        for (int u = 0; u < n; u++) {
            if (degree[u] == 0) {
                if (ans != -1) {
                    return -1;
                }
                ans = u;
            }
        }
        return ans;
    }
};
