#define MOD 1000000007

class Solution {
public:
    int numOfArrays(int n, int m, int k) {
        // dp[i][j][c] = number of arrays of size i where the cost ends in c and initial maximum_value is j.
        vector<vector<vector<int>>> dp(2, vector<vector<int>>(m+1, vector<int>(k+1)));

        for (int i = 0; i <= n; i++) {
            int ri = i&1;
            for (int j = 0; j <= m; j++) {
                for (int c = 0; c <= k; c++) {
                    int &ans = dp[ri][j][c];
                    ans = 0;
                    if (i == 0) {
                        if (c == 0) ans = 1;
                        continue;
                    }

                    for (int nj = 1; nj <= m; nj++) {
                        if (nj <= j) {
                            ans = (ans + dp[ri^1][j][c]) % MOD;
                        } else if (c > 0) {
                            ans = (ans + dp[ri^1][nj][c-1]) % MOD;
                        }
                    }
                }
            }
        }
        
        return dp[n&1][0][k];
    }
};
