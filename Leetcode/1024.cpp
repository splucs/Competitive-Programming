class Solution {
public:
    int videoStitching(vector<vector<int>>& clips, int time) {
        int last = 0, best = 0, ans = 0;
        sort(clips.begin(), clips.end());
        for (vector<int>& clip : clips) {
            int st = clip[0], en = clip[1];
            if (best < st && best < time) {
                return -1;
            }
            if (last < st) {
                ans++;
                last = best;
            }
            if (last >= time) {
                break;
            }
            best = max(best, en);
        }
        if (last < time) {
            ans++;
            last = best;
        }
        if (last < time) {
            return -1;
        }
        return ans;
    }
};
