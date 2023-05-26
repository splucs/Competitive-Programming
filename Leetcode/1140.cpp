class Solution {
public:
    int stoneGameII(vector<int>& piles) {
        int n = piles.size();
        // dp[i][m] = maximum balance given it's our turn, we're at pile i and M = m
        vector<vector<int> > dp(n+1, vector<int>(n+1, 0));

        int pileSum = 0;
        for (int i = n-1; i >= 0; i--) {
            pileSum += piles[i];

            // sum[j] = sum of the next j elements including i
            vector<int> sum(n-i+1, 0);
            for (int x = 1; x <= n-i; x++) {
                sum[x] = sum[x-1] + piles[i+x-1];
            }

            for (int m = 1; m <= n; m++) {
                dp[i][m] = -1e7;
                for (int x = 1; x <= 2*m && x <= n-i; x++) {
                    int nm = m > x ? m : x;
                    if (nm >= n) nm = n;

                    int cur = sum[x] - dp[i+x][nm];
                    if (cur > dp[i][m]) {
                        dp[i][m] = cur;
                    }
                }
            }
        }

        return (dp[0][1] + pileSum)/2;
    }
};
