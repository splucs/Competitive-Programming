class Solution {
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int n = profit.size();

        // Reduce values of startTime and endTime such that 0 <= value <= 2*n;
        map<int, int> redux;
        for (int v : startTime) redux[v] = 0;
        for (int v : endTime) redux[v] = 0;
        int seen = 0;
        for (auto &entry : redux) {
            entry.second = seen++;
        }
        for (int i = 0; i < n; i++) startTime[i] = redux[startTime[i]];
        for (int i = 0; i < n; i++) endTime[i] = redux[endTime[i]];
    
        // Get indexes in increasing order of endTime.
        vector<int> idx(n, 0);
        for (int i = 0; i < n; i++) {
            idx[i] = i;
        }
        sort(idx.begin(), idx.end(), [&](int i, int j) {
            return endTime[i] < endTime[j];
        });

        // dp[t] = max profit up to time t
        vector<int> dp(seen);
        for (int t = 0, jt = 0, j; t < seen; t++) {
            dp[t] = (t > 0 ? dp[t-1] : 0);
            while (jt < n && endTime[idx[jt]] <= t) {
                int j = idx[jt];
                dp[t] = max(dp[t], profit[j] + dp[startTime[j]]);
                jt++;
            }
        }
        return dp[seen-1];
    }
};
