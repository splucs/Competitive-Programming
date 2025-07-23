class Solution {
public:
    int maxAscendingSum(vector<int>& nums) {
        int curSum = nums[0], ans = nums[0];
        for (int i = 1; i < (int)nums.size(); i++) {
            if (nums[i] <= nums[i-1]) {
                curSum = 0;
            }
            curSum += nums[i];
            ans = max(ans, curSum);
        }
        return ans;
    }
};
