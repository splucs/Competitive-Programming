class Solution {
public:
    int maxValue(vector<vector<int>>& events, int k) {
        sort(events.begin(), events.end());
        int n = events.size();
#define start(x) x[0]
#define end(x) x[1]
#define value(x) x[2]

        // next[i] = index of earliest event that I can attend after I attend event i
        vector<int> next(n);
        for (int i = n-1; i >= 0; i--) {
            int hi = n, lo = i;
            while (hi > lo+1) {
                int mid = (hi+lo)>>1;
                if (start(events[mid]) > end(events[i])) hi = mid;
                else lo = mid;
            }
            next[i] = hi;
        }

        // dp[i][j] = maximum value given I'm available at event i and can attend j+1 more.
        vector<vector<int>> dp(n, vector<int>(k));
        for (int i = n-1; i >= 0; i--) {
            int ni = next[i];
            for (int j = 0; j < k; j++) {
                int opt1 = i+1 < n ? dp[i+1][j] : 0;
                int opt2 = value(events[i]) + (ni < n && j > 0 ? dp[ni][j-1] : 0);
                dp[i][j] = opt1 > opt2 ? opt1 : opt2;
            }
        }

        return dp[0][k-1];
    }
};

