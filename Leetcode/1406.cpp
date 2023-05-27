class Solution {
public:
    string stoneGameIII(vector<int>& stoneValue) {
        int n = stoneValue.size();
        int dp[4];

        dp[n & 3] = 0;
        for (int i = n-1; i >= 0; i--) {
            int &ans = dp[i & 3];
            ans = -1e7;

            int curTurnValue = 0;
            for (int x = 1; x <= 3 && i+x-1 < n; x++) {
                curTurnValue += stoneValue[i+x-1];

                int cur = curTurnValue - dp[(i+x) & 3];
                ans = (ans > cur ? ans : cur);
            }
        }

        if (dp[0] == 0) return "Tie";
        return dp[0] > 0 ? "Alice" : "Bob";
    }
};
