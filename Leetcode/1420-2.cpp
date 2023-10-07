#define MOD 1000000007

class Solution {
public:
    int numOfArrays(int n, int m, int k) {
        // dp[i][j][c] = number of arrays of size i where the cost ends in c and initial maximum_value is j.
        vector<vector<vector<int>>> dp(2, vector<vector<int>>(m+1, vector<int>(k+1)));
        // sum[i][j][c] = sum of dp[i][t][c] for j <= t <= m.
        vector<vector<vector<int>>> sum(2, vector<vector<int>>(m+1, vector<int>(k+1)));

        for (int i = 0; i <= n; i++) {
            int ri = i&1;
            for (int j = m; j >= 0; j--) {
                for (int c = 0; c <= k; c++) {
                    int &ans = dp[ri][j][c];
                    int &ansSum = sum[ri][j][c];
                    ans = 0;
                    if (i == 0) {
                        if (c == 0) {
                            ans = 1;
                            ansSum = m-j+1;
                        }
                        continue;
                    }

                    ans = (ans + j*1ll*dp[ri^1][j][c]) % MOD;
                    if (j < m && c > 0) {
                        ans = (ans + sum[ri^1][j+1][c-1]) % MOD;
                    }

                    ansSum = ans;
                    if (j < m) ansSum = (ansSum + sum[ri][j+1][c]) % MOD;
                }
            }
        }
        
        return dp[n&1][0][k];
    }
};
