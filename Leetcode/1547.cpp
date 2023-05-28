class Solution {
public:
    int minCost(int n, vector<int>& cuts) {
        cuts.push_back(0);
        cuts.push_back(n);
        sort(cuts.begin(), cuts.end());
        
        int nc = cuts.size();
        vector<vector<int> > dp(nc+1, vector<int>(nc+1));

        for (int l = 1; l < nc; l++) {
            for (int i = 0; i+l < nc; i++) {
                int j = i+l;
                if (l == 1) {
                    dp[i][j] = 0;
                    continue;
                }

                int &ans = dp[i][j];
                ans = 1e8;
                int cost = cuts[j] - cuts[i];
                for (int k = i+1; k < j; k++) {
                    int cur = cost + dp[i][k] + dp[k][j];
                    if (ans > cur) ans = cur;
                }
            }
        }
        return dp[0][nc-1];
    }
};
