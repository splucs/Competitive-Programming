class Solution {
public:
    int longestSubsequence(string s, int k) {
        vector<char> digits;
        for(; k > 0; k >>= 1) {
            digits.push_back((k&1) + '0');
        }
        reverse(digits.begin(), digits.end());

        int n = s.size(), m = digits.size();
        vector<vector<vector<int>>> dp(n+1, vector<vector<int>>(m+1, vector<int>(2, 0)));
        for (int i = n-1; i >= 0; i--) {
            for (int j = 0; j < m; j++) {
                dp[i][j][1] = 1 + dp[i+1][j+1][1];
                dp[i][j][0] = dp[i+1][j][0];
                if (s[i] == digits[j]) {
                    dp[i][j][0] = max(dp[i][j][0], 1 + dp[i+1][j+1][0]);
                }
                if (s[i] < digits[j]) {
                    dp[i][j][0] = max(dp[i][j][0], 1 + dp[i+1][j+1][1]);
                }
            }
        }
        int ans = 0, leadingZeroes = 0;
        for (int i = 0; i < n; i++) {
            ans = max(ans, leadingZeroes + dp[i][0][0]);
            ans = max(ans, leadingZeroes + min(n-i, m-1));
            if (s[i] == '0') {
                leadingZeroes++;
            }
        }
        return ans;
    }
};
