class Solution {
private:
    vector<bool> safe;
    vector<int> viz;
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n = graph.size();
        safe.assign(n, true);
        viz.assign(n, 0);
        for (int u = 0; u < n; u++) {
            if (viz[u] == 0) dfs(u, graph);
        }
        vector<int> ans;
        for (int u = 0; u < n; u++) {
            if (safe[u]) ans.push_back(u);
        }
        return ans;
    }
    void dfs(int u, vector<vector<int>>& graph) {
        viz[u] = 1;
        for (int v : graph[u]) {
            if (viz[v] == 0) {
                dfs(v, graph);
            } else if (viz[v] == 1) {
                safe[u] = false;
            }
            safe[u] = safe[u] && safe[v];
        }
        viz[u] = 2;
    }
};
