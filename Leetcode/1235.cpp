class Solution {
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int n = profit.size();

        // idx are the indices 0...n-1 sorted by endTime[i].
        vector<int> idx(n, 0);
        for (int i = 0; i < n; i++) {
            idx[i] = i;
        }
        sort(idx.begin(), idx.end(), [&](int i, int j) {
            return endTime[i] < endTime[j];
        });

        // dp[it] = max profit up to time that job idx[it] end.
        vector<int> dp(n);
        for (int it = 0; it < n; it++) {
            dp[it] = it > 0 ? dp[it-1] : 0;
            int i = idx[it];

            int lo = -1, hi = it;
            while (hi > lo + 1) {
                int mid = (hi+lo)>>1;
                int j = idx[mid];
                if (endTime[j] <= startTime[i]) lo = mid;
                else hi = mid;
            }
            
            int cur = profit[i];
            if (lo >= 0) cur += dp[lo];
            dp[it] = max(dp[it], cur);
        }

        return dp[n-1];
    }
};
