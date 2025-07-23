class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> pref(nums.begin(), nums.end());
        vector<int> suff(nums.begin(), nums.end());
        int n = nums.size();
        for (int i = 1; i < n; i++) {
            pref[i] *= pref[i-1];
        }
        for (int i = n-2; i >= 0; i--) {
            suff[i] *= suff[i+1];
        }
        nums[0] = suff[1];
        nums[n-1] = pref[n-2];
        for (int i = 1; i < n-1; i++) {
            nums[i] = pref[i-1]*suff[i+1];
        }
        return nums;
    }
};
