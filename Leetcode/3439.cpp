class Solution {
public:
    int maxFreeTime(int eventTime, int k, vector<int>& startTime, vector<int>& endTime) {
        vector<int> intervals;
        int n = startTime.size();
        intervals.reserve(n+1);
        int prev = 0;
        for (int i = 0; i < n; i++) {
            intervals.push_back(startTime[i] - prev);
            prev = endTime[i];
        }
        intervals.push_back(eventTime - prev);
        int cur = 0;
        for (int i = 0; i <= k; i++) {
            cur += intervals[i];
        }
        int ans = cur;
        for (int i = k+1, j = 0; i <= n; i++, j++) {
            cur += intervals[i] - intervals[j];
            ans = max(ans, cur);
        }
        return ans;
    }
};
