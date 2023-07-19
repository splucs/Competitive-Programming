class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());
        int longestEnd = 0;
        int n = intervals.size();

        int ans = 0;
        for (int i = 1; i < n; i++) {
            // Check no overlap
            if (intervals[i][0] >= intervals[longestEnd][1]) {
                longestEnd = i;
                continue;
            }
            ans++;

            if (intervals[i][1] > intervals[longestEnd][1]) {
                // remove i
            } else {
                // remove longestEnd
                longestEnd = i;
            }
        }
        return ans;
    }
};
