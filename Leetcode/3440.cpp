class Solution {
private:
    int maxFreeTimeRight(int eventTime, vector<int>& startTime, vector<int>& endTime) {
        int n = startTime.size();
        vector<int> interval(n+1);
        int prev = 0;
        for (int i = 0; i < n; i++) {
            interval[i] = startTime[i] - prev;
            prev = endTime[i];
        }
        interval[n] = eventTime - prev;

        int ans = interval[n] + interval[n-1];
        int maxInterval = 0, duration;
        for (int i = n-2; i >= 0; i--) {
            maxInterval = max(maxInterval, interval[i+2]);
            duration = endTime[i] - startTime[i];
            if (maxInterval >= duration) {
                ans = max(ans, interval[i] + duration + interval[i+1]);
            } else {
                ans = max(ans, interval[i] + interval[i+1]);
            }
        }
        return ans;
    }
public:
    int maxFreeTime(int eventTime, vector<int>& startTime, vector<int>& endTime) {
        int n = startTime.size();
        int ans = maxFreeTimeRight(eventTime, startTime, endTime);
        reverse(startTime.begin(), startTime.end());
        reverse(endTime.begin(), endTime.end());
        for (int i = 0; i < n; i++) {
            startTime[i] = eventTime - startTime[i];
            endTime[i] = eventTime - endTime[i];
        }
        return max(ans, maxFreeTimeRight(eventTime, endTime, startTime));
    }
};
