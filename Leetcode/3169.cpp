class Solution {
public:
    int countDays(int days, vector<vector<int>>& meetings) {
        sort(meetings.begin(), meetings.end());
        int ans = 0;
        int lastMeeting = 0;
        for (const vector<int>& meeting : meetings) {
            int start = meeting[0], end = meeting[1];
            if (lastMeeting < start) {
                ans += start - lastMeeting - 1;
            }
            lastMeeting = max(lastMeeting, end);
        }
        if (lastMeeting < days) {
            ans += days - lastMeeting;
        }
        return ans;
    }
};
