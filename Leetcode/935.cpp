#define MOD 1000000007

class Solution {
    vector<vector<int>> g = {
        {4, 6}, // 0
        {6, 8}, // 1
        {7, 9}, // 2
        {4, 8}, // 3
        {3, 9, 0}, // 4
        {}, // 5
        {1, 7, 0}, // 6
        {2, 6}, // 7
        {1, 3}, // 8
        {2, 4} // 9
    };
public:
    int knightDialer(int n) {
        vector<int> dp[2];
        dp[1].assign(10, 1);

        for (int i = 2; i <= n; i++) {
            int ri = i&1;
            dp[ri].assign(10, 0);
            for (int u = 0; u < 10; u++) {
                for (int v : g[u]) {
                    dp[ri][u] = (dp[ri][u] + dp[ri^1][v]) % MOD;
                }
            }
        }

        int ans = 0;
        for (int u = 0; u < 10; u++) {
            ans = (ans + dp[n&1][u]) % MOD;
        }
        return ans;
    }
};
