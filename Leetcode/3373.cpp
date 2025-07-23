class Solution {
    vector<vector<int>> g[2];
    vector<int> parity[2];
    vector<int> parityCnt[2];
    void dfs(int t, int u, int p, int curPar) {
        parity[t][u] = curPar;
        parityCnt[t][curPar]++;
        for (int v : g[t][u]) {
            if (v == p) {
                continue;
            }
            dfs(t, v, u, curPar^1);
        }
    }
public:
    vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
        int n = edges1.size() + 1;
        int m = edges2.size() + 1;
        if (n == 1 && m == 1) {
            return {1};
        }
        g[0].resize(n);
        for (const vector<int>& edge : edges1) {
            int u = edge[0], v = edge[1];
            g[0][u].push_back(v);
            g[0][v].push_back(u);
        }
        g[1].resize(m);
        for (const vector<int>& edge : edges2) {
            int u = edge[0], v = edge[1];
            g[1][u].push_back(v);
            g[1][v].push_back(u);
        }

        parity[0].resize(n);
        parity[1].resize(m);
        parityCnt[0].assign(2, 0);
        parityCnt[1].assign(2, 0);
        dfs(0, 0, -1, 0);
        dfs(1, 0, -1, 0);

        vector<int> ans(n);
        int maxParity2 = max(parityCnt[1][0], parityCnt[1][1]);
        for (int u = 0; u < n; u++) {
            ans[u] = parityCnt[0][parity[0][u]] + maxParity2;
        }
        return ans;
    }
};
