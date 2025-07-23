class Solution {
private:
    vector<bitset<100>> isPreReq;
    vector<vector<int>> g;
    vector<bool> viz;
    void dfs(int u) {
        if (viz[u]) {
            return;
        }
        viz[u] = true;
        isPreReq[u][u] = true;
        for (int v : g[u]) {
            dfs(v);
            isPreReq[u] |= isPreReq[v];
        }
    }
public:
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        isPreReq.assign(numCourses, bitset<100>());
        g.assign(numCourses, vector<int>());
        viz.assign(numCourses, false);
        for (const vector<int>& prereq : prerequisites) {
            int u = prereq[0], v = prereq[1];
            g[u].push_back(v);
        }

        for (int u = 0; u < numCourses; u++) {
            dfs(u);
        }

        vector<bool> ans;
        ans.reserve(queries.size());
        for (const vector<int>& query : queries) {
            int u = query[0], v = query[1];
            ans.push_back(isPreReq[u][v]);
        }

        return ans;
    }
};
