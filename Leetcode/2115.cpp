class Solution {
private:
    unordered_map<string, int> reduced;
    vector<int> viz;
    vector<vector<int>> g;

    int reduce(string& s) {
        if (!reduced.count(s)) {
            reduced[s] = reduced.size();
            viz.push_back(-1);
            g.push_back(vector<int>());
        }
        return reduced[s];
    }
    int dfs(int u) {
        if (viz[u] != 0) {
            return viz[u];
        }
        viz[u] = -1;
        for (int v : g[u]) {
            if (dfs(v) == -1) {
                return -1;
            }
        }
        viz[u] = 1;
        return 1;
    }
public:
    vector<string> findAllRecipes(vector<string>& recipes, vector<vector<string>>& ingredients, vector<string>& supplies) {
        for (int i = 0; i < (int)recipes.size(); i++) {
            int u = reduce(recipes[i]);
            for (string& ingredient : ingredients[i]) {
                int v = reduce(ingredient);
                g[u].push_back(v);
            }
        }
        for(string& recipe : recipes) {
            viz[reduce(recipe)] = 0;
        }
        for (string& supply : supplies) {
            viz[reduce(supply)] = 1;
        }
        vector<string> ans;
        for(string& recipe : recipes) {
            if (dfs(reduce(recipe)) == 1) {
                ans.push_back(recipe);
            }
        }
        return ans;
    }
};
