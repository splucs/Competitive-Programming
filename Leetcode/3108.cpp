class Solution {
private:
    vector<int> color;
    vector<int> colorMask;
    vector<vector<pair<int, int>>> g;
    void dfs(int u, int c) {
        color[u] = c;
        for (pair<int, int>& e : g[u]) {
            int v = e.second;
            int w = e.first;
            colorMask[c] &= w;
            if (color[v] == -1) {
                dfs(v, c);
            }
        }
    }
public:
    vector<int> minimumCost(int n, vector<vector<int>>& edges, vector<vector<int>>& query) {
        g.resize(n);
        for (vector<int>& e : edges) {
            int u = e[0], v = e[1], w = e[2];
            g[u].push_back(make_pair(w, v));
            g[v].push_back(make_pair(w, u));
        }

        color.assign(n, -1);
        int numColors = 0;
        for (int u = 0; u < n; u++) {
            if (color[u] == -1) {
                colorMask.push_back(~0);
                dfs(u, numColors++);
            }
        }

        vector<int> ans;
        ans.reserve(query.size());
        for (vector<int>& q : query) {
            int s = q[0], t = q[1];
            if (color[s] != color[t]) {
                ans.push_back(-1);
            } else {
                ans.push_back(colorMask[color[s]]);
            }
        }
        return ans;
    }
};
