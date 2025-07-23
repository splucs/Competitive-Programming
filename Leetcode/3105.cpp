class Solution {
public:
    int longestMonotonicSubarray(vector<int>& nums) {
        int curInc = 1, curDec = 1;
        int ans = 1;
        for (int i = 1; i < (int)nums.size(); i++) {
            if (nums[i] >= nums[i-1]) {
                curDec = 0;
            }
            if (nums[i] <= nums[i-1]) {
                curInc = 0;
            }
            curInc++;
            curDec++;
            ans = max(ans, max(curInc, curDec));
        }
        return ans;
    }
};
