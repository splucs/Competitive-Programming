class Solution {
public:
    int minimumTeachings(int n, vector<vector<int>>& languages, vector<vector<int>>& friendships) {
        int m = languages.size();
        vector<vector<int>> g(m+1);
        for (const vector<int>& e : friendships) {
            int u = e[0], v = e[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }

        vector<vector<bool>> knows(m+1, vector<bool>(n+1, false));
        for (int u = 1; u <= m; u++) {
            for (int l : languages[u-1]) {
                knows[u][l] = true;
            }
        }

        vector<int> minCost(n+1, 0);
        for (int u = 1; u <= m; u++) {
            bool canTalkToAllFriends = true;
            for (int v : g[u]) {
                bool foundCommonLanguage = false;
                for (int l : languages[u-1]) {
                    if (knows[v][l]) {
                        foundCommonLanguage = true;
                        break;
                    }
                }
                if (!foundCommonLanguage) {
                    canTalkToAllFriends = false;
                    break;
                }
            }

            if (canTalkToAllFriends) {
                continue;
            }

            for (int l = 1; l <= n; l++) {
                if (!knows[u][l]) {
                    minCost[l]++;
                }
            }
        }

        int ans = m;
        for (int l = 1; l <= n; l++) {
            ans = min(ans, minCost[l]);
        }
        return ans;
    }
};
