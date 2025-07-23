class Solution {
public:
    long long maximumTripletValue(vector<int>& nums) {
        int n = nums.size();
        long long ans = 0;
        vector<int> maxAfter(n, 0);
        for (int k = n-2; k >= 0; k--) {
            maxAfter[k] = max(nums[k+1], maxAfter[k+1]);
        }
        int maxBefore = 0;
        for (int j = 0; j < n; j++) {
            ans = max(ans, (maxBefore - nums[j])*(long long)maxAfter[j]);
            maxBefore = max(nums[j], maxBefore);
        }
        return ans;
    }
};
