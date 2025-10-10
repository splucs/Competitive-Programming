class Solution {
public:
    int triangularSum(vector<int>& nums) {
        for (int n = nums.size() - 1; n >= 0; n--) {
            for (int i = 0; i < n; i++) {
                nums[i] = (nums[i] + nums[i+1]) % 10;
            }
        }
        return nums[0];
    }
};
