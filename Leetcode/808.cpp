class Solution {
private:
    int di[4] = {-4, -3, -2, -1};
    int dj[4] = {0, -1, -2, -3};
    const int MAXN = 175;
public:
    double soupServings(int n) {
        n = (n+24)/25;
        if (n > 5000) return 1;

        // Conjecture: the answer converges and MAXN is enough precision
        if (n > MAXN) n = MAXN;

        // dp[i][j] = answer given I have i*25ml of A and j*25ml of B
        vector<vector<double>> dp(n+1, vector<double>(n+1));

        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                double &ans = dp[i][j];

                // Base cases
                if (i == 0 || j == 0) {
                    if (i == j) ans = 0.5;
                    else if (i == 0) ans = 1;
                    else ans = 0;
                    continue;
                }

                // Recursion
                ans = 0;
                for (int k = 0; k < 4; k++) {
                    int ni = i + di[k];
                    if (ni < 0) ni = 0;
                    int nj = j + dj[k];
                    if (nj < 0) nj = 0;
                    ans += dp[ni][nj];
                }
                ans *= 0.25;
            }
        }
        return dp[n][n];
    }
};
