#define INF 0x3f3f3f3f
class Solution {
public:
    int maxIncreasingSubarrays(vector<int>& nums) {
        int prevStreak = 0, curStreak = 0;
        int prev = -INF, ans = 0;
        for (int num : nums) {
            if (num > prev) {
                curStreak++;
            } else {
                prevStreak = curStreak;
                curStreak = 1;
            }
            ans = max(ans, min(prevStreak, curStreak));
            ans = max(ans, curStreak/2);
            prev = num;
        }
        return ans;
    }
};
