class Solution {
private:
    vector<vector<int>> g;
    vector<int> viz;
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        int n = numCourses;
        g.resize(n);
        for(vector<int> &req : prerequisites) {
            g[req[1]].push_back(req[0]);
        }

        viz.assign(n, 0);
        for (int u = 0; u < n; u++) {
            if (viz[u] == 0 && !dfs(u)) return false;
        }
        return true;
    }
    bool dfs(int u) {
        viz[u] = 1;
        for (int v : g[u]) {
            if (viz[v] == 0) {
                if (!dfs(v)) return false;
            } else if (viz[v] == 1) {
                return false;
            }
        }
        viz[u] = 2;
        return true;
    }
};
