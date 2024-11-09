class Solution {
public:
    int findMinDifference(vector<string>& timePoints) {
        int n = timePoints.size();
        vector<int> minutes;
        minutes.reserve(n);
        for (string& time: timePoints) {
            int h = (time[0] - '0')*10 + (time[1] - '0');
            int m = (time[3] - '0')*10 + (time[4] - '0');
            minutes.push_back(h*60 + m);
        }
        sort(minutes.begin(), minutes.end());
        int ans = 24*60;
        for (int i = 1; i < n; i++) {
            ans = min(ans, minutes[i] - minutes[i-1]);
        }
        ans = min(ans, 24*60 - minutes[n-1] + minutes[0]);
        return ans;
    }
};
