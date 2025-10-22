class Solution {
public:
    long long maximumTotalDamage(vector<int>& power) {
        sort(power.begin(), power.end());
        int n = power.size();
        vector<long long> dp(n, 0);
        long long ans = 0, maxDp = 0;
        for (int i = 0, j = -1; i < n;) {
            int ni = i;
            for(; ni < n && power[i] == power[ni]; ni++);

            while(power[j+1] < power[i]-2) {
                maxDp = max(maxDp, dp[++j]);
            }
            for (int it = i; it < ni; it++) {
                dp[it] = maxDp + (it - i + 1LL)*power[i];
                ans = max(ans, dp[it]);
            }
            i = ni;
        }
        return ans;
    }
};
