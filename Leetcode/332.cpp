class Solution {
private:
    map<string, int> name2id;
    vector<string> id2name;
    vector<vector<int>> g;
    int getNode(string s) {
        if (!name2id.count(s)) {
            int u = id2name.size();
            id2name.push_back(s);
            g.push_back(vector<int>());
            name2id[s] = u;
        }
        return name2id[s];
    }
    vector<int> work;
    vector<string> ans;
    void dfs(int u) {
        for (int &e = work[u]; e < (int)g[u].size();) {
            int v = g[u][e];
            e++;
            dfs(v);
        }
        ans.push_back(id2name[u]);
    }
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        // Build graph
        for (vector<string> &ticket : tickets) {
            string &from = ticket[0];
            string &to = ticket[1];
            int u = getNode(from);
            int v = getNode(to);
            g[u].push_back(v);
        }

        // Sort edges
        int n = id2name.size();
        for (int u = 0; u < n; u++) {
            sort(g[u].begin(), g[u].end(), [=](int i, int j) {
                return id2name[i] < id2name[j];
            });
        }

        // Call dfs
        work.assign(n, 0);
        dfs(getNode("JFK"));
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
