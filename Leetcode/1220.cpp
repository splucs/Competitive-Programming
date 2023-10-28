typedef int column[5];
typedef int matrix[5][5];

class Solution {
private:
    const int MOD = 1e9 + 7;
    const matrix recursion = {
        {0, 1, 0, 0, 0}, // 'a' can only go to 'e'
        {1, 0, 1, 0, 0}, // 'e' can only go to 'a' or 'i'
        {1, 1, 0, 1, 1}, // 'i' can only go to 'a', 'e', 'o' or 'u'
        {0, 0, 1, 0, 1}, // 'o' can only go to 'i' or 'u'
        {1, 0, 0, 0, 0}, // 'u' can only go to 'a'
    };
public:
    int countVowelPermutation(int n) {
        // dp[i][j] = how many strings of size i that end in j
        vector<column> dp(2);

        for (int j = 0; j < 5; j++) dp[1][j] = 1;

        for (int i = 2; i <= n; i++) {
            int ri = i&1;
            for (int j = 0; j < 5; j++) {
                int &ans = dp[ri][j];
                ans = 0;
                for (int k = 0; k < 5; k++) {
                    if (recursion[j][k] == 1) {
                        ans = (ans + dp[ri^1][k]) % MOD;
                    }
                }
            }
        }

        int ans = 0;
        for (int j = 0; j < 5; j++) {
            ans = (ans + dp[n&1][j]) % MOD;
        }
        return ans;
    }
};
