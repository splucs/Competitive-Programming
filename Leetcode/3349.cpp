class Solution {
public:
    bool hasIncreasingSubarrays(vector<int>& nums, int k) {
        int prevStreak = 0, curStreak = 0;
        int prev = -2000;
        for (int num : nums) {
            if (num > prev) {
                curStreak++;
            } else {
                prevStreak = curStreak;
                curStreak = 1;
            }
            if (prevStreak >= k && curStreak >= k) {
                return true;
            }
            if (curStreak >= k+k) {
                return true;
            }
            prev = num;
        }
        return false;
    }
};
