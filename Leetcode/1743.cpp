class Solution {
public:
    vector<int> restoreArray(vector<vector<int>>& adjacentPairs) {
        unordered_map<int, vector<int>> g;
        set<int> borders;
        for (vector<int> &e : adjacentPairs) {
            int u = e[0];
            int v = e[1];
            g[u].push_back(v);
            g[v].push_back(u);

            if (g[u].size() == 1) borders.insert(u);
            else borders.erase(u);
            if (g[v].size() == 1) borders.insert(v);
            else borders.erase(v);
        }

        int u = *borders.begin();
        int prev = 1e7;
        vector<int> ans;
        for(bool over = false; !over;) {
            ans.push_back(u);
            over = true;
            for (int v : g[u]) {
                if (v == prev) continue; 
                prev = u;
                u = v;
                over = false;
                break;
            }
        }
        return ans;
    }
};
