class Solution {
private:
    bool detonates(vector<vector<int>>& bombs, int i, int j) {
        long long d2 = (bombs[i][0] - bombs[j][0])*1ll*(bombs[i][0] - bombs[j][0]) + (bombs[i][1] - bombs[j][1])*1ll*(bombs[i][1] - bombs[j][1]);
        long long r2 = bombs[i][2]*1ll*bombs[i][2];
        return d2 <= r2;
    }
public:
    int maximumDetonation(vector<vector<int>>& bombs) {
        int n = bombs.size();
        vector<vector<bool>> g(n, vector<bool>(n, false));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (detonates(bombs, i, j)) {
                    g[i][j] = true;
                }
            }
        }

        // Modification of floyd-warshall
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                if (!g[i][k]) continue;
                for (int j = 0; j < n; j++) {
                    if (!g[k][j]) continue;
                    g[i][j] = true;
                }
            }
        }

        int ans = 0;
        for (int i = 0; i < n; i++) {
            int cur = 0;
            for (int j = 0; j < n; j++) {
                if (g[i][j]) cur++;
            }
            ans = (cur > ans ? cur : ans);
        }
        return ans;
    }
};
