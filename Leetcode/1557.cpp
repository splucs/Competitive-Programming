class Solution {
public:
    vector<int> findSmallestSetOfVertices(int n, vector<vector<int>>& edges) {
        vector<int> incoming(n, 0);
        for (vector<int> &e : edges) {
            incoming[e[1]]++;
        }
        vector<int> ans;
        for (int u = 0; u < n; u++) {
            if (incoming[u] == 0) ans.push_back(u);
        }
        return ans;
    }
};
