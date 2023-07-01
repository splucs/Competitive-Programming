class Solution {
public:
    int distributeCookies(vector<int>& cookies, int k) {
        int n = cookies.size();
        int maxMask = 1<<n;
        vector<int> sum(maxMask, 0);
        for (int mask = 0; mask < maxMask; mask++) {
            for (int i = 0; i < n; i++) {
                if (mask&(1<<i)) sum[mask] += cookies[i];
            }
        }

        // dp[j][mask] = minimal unfairness to distribute the cookies in mask among j+1 kids.
        vector<vector<int>> dp(k, vector<int>(maxMask));
        for (int j = 0; j < k; j++) {
            for (int mask = 0; mask < maxMask; mask++) {
                dp[j][mask] = sum[mask];
                if (j == 0) {
                    continue;
                }

                for (int subMask = mask; subMask; subMask=(subMask-1)&mask) {
                    int opt1 = dp[j-1][mask^subMask];
                    int opt2 = sum[subMask];
                    int unfairness = opt1 > opt2 ? opt1 : opt2;
                    dp[j][mask] = dp[j][mask] > unfairness ? unfairness : dp[j][mask];
                }
            }
        }
        return dp[k-1][maxMask-1];
    }
};
