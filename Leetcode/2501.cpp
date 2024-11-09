class Solution {
public:
    int longestSquareStreak(vector<int>& nums) {
        map<long long, int> dp;
        for (const int& x : nums) {
            dp[x] = 1;
        }
        int ans = 1;
        for (const pair<int, int>& entry : dp) {
            const long long& x = entry.first;
            const int& val = entry.second;
            ans = max(ans, val);
            if (dp.count(x*x)) {
                dp[x*x] += val;
            }
        }
        return ans > 1 ? ans : -1;
    }
};
