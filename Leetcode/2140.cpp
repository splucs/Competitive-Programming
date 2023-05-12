class Solution {
public:
    long long mostPoints(vector<vector<int>>& questions) {
        int n = questions.size();
        vector<long long> dp(n+1);
        dp[n] = 0;
        for (int i = n-1; i >= 0; i--) {
            dp[i] = dp[i+1];
            long long q = questions[i][0];
            int j = i + questions[i][1] + 1;
            if (j < n) q += dp[j];
            if (q > dp[i]) dp[i] = q;
        }
        return dp[0];
    }
};
