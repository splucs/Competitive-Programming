#define MOD 1000000007
class Solution {
public:
    int possibleStringCount(string word, int k) {
        vector<int> rep, repSum;
        int cnt = 1, n = word.size();
        for (int i = 1; i < n; i++) {
            if (word[i] == word[i-1]) {
                cnt++;
                continue;
            }
            if (cnt > 1) {
                rep.push_back(cnt-1);
            }
            k--;
            cnt = 1;
        }
        if (cnt > 1) {
            rep.push_back(cnt-1);
        }
        k--;

        int ans = 1;
        for (int r : rep) {
            ans = (ans * (long long)(r+1)) % MOD;
        }
        if (k <= 0) {
            return ans;
        }

        int m = rep.size();
        vector<int> dp(k), dpSum(k);
        for (int j = 0; j < k; j++) {
            dpSum[j] = j+1;
        }
        for (int i = m-1; i >= 0; i--) {
            dp[0] = dpSum[min(rep[i], k-1)];
            for (int j = 1; j < k; j++) {
                // dp[i][j] = dp[i+1][j] + ... + dp[i+1][j+rep[i]];
                dp[j] = (dpSum[min(j+rep[i], k-1)] - dpSum[j-1] + MOD) % MOD;
            }

            dpSum[0] = dp[0];
            for (int j = 1; j < k; j++) {
                dpSum[j] = (dpSum[j-1] + dp[j]) % MOD;
            }
        }

        ans = (ans - dp[0] + MOD) % MOD;
        return ans;
    }
};
