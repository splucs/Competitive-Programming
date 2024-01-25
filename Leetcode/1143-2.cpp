class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int n = text1.size(), m = text2.size();
        vector<vector<int>> dp(3, vector<int>(n));

        for (int s = 0; s < n+m-1; s++) {
            int sr = s%3;
            for (int i = max(s - m + 1, 0); i < n && i <= s; i++) {
                int j = s-i;
                int &ans = dp[sr][i];

                ans = text1[i] == text2[j] ? 1 : 0;
                if (i > 0 && j > 0) {
                    ans += dp[(sr+1)%3][i-1];
                }

                if (i > 0) {
                    ans = max(ans, dp[(sr+2)%3][i-1]);
                }
                if (j > 0) {
                    ans = max(ans, dp[(sr+2)%3][i]);
                }
            }
        }

        return dp[(n+m-2)%3][n-1];
    }
};
