#define MOD 1000000007

class Solution {
public:
    int numFactoredBinaryTrees(vector<int>& arr) {
        sort(arr.begin(), arr.end());
        int n = arr.size();

        // dp[i] = how many trees exist that have arr[i] as root.
        vector<int> dp(n, 1);
        for (int i = 0; i < n; i++) {
            for (int pi = 0, j = 0; j <= i && pi < n; j++) {
                long long prod = arr[i]*1ll*arr[j];
                while (pi < n && arr[pi] < prod) pi++;
                if (pi == n) break;
                if (arr[pi] > prod) continue;

                // If i and j are different, there are two possibilities because of ordering.
                long long mult = i == j ? 1 : 2;
                dp[pi] = (dp[pi] + dp[i]*mult*dp[j]) % MOD;
            }
        }

        int ans = 0;
        for (int i = 0; i < n; i++) {
            ans = (ans + dp[i]) % MOD;
        }
        return ans;
    }
};
