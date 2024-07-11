class Solution {
public:
    int minDifference(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        if (n <= 4) {
            return 0;
        }

        int ans = nums[n-4] - nums[0];
        for (int i = 1; i <= 3; i++) {
            ans = min(ans, nums[i+n-4] - nums[i]);
        }
        return ans;
    }
};
