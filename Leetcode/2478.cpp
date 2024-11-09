#define MOD 1000000007
class Solution {
public:
    int beautifulPartitions(string s, int k, int minLength) {
        bool isPrime[10] = {false, false, true, true, false, true, false, true, false, false};

        int n = s.size();
        // dp[i][j] = how many partitions starting at i with j elements.
        vector<vector<int>> dp(n+1, vector<int>(k+1, 0));
        dp[n][0] = 1;
        // sum[i][j] = sum of dp[t][j] where i <= t <= n and s[t-1] is not prime or t == 0.
        vector<vector<int>> sum(n+1, vector<int>(k+1, 0));
        sum[n][0] = isPrime[s[n-1]-'0'] ? 0 : 1;
        
        for (int i = n-1; i >= 0; i--) {
            if (isPrime[s[i]-'0'] && i+minLength <= n) {
                for (int j = 1; j <= k; j++) {
                    dp[i][j] = sum[i+minLength][j-1];
                }
            }
            if (i == 0 || !isPrime[s[i-1]-'0']) {
                for (int j = 0; j <= k; j++) {
                    sum[i][j] = (dp[i][j] + sum[i+1][j]) % MOD;
                }
            } else {
                for (int j = 0; j <= k; j++) {
                    sum[i][j] = sum[i+1][j];
                }
            }
        }
        return dp[0][k];
    }
};
