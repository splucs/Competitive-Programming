class Solution {
public:
    long long countFairPairs(vector<int>& nums, int lower, int upper) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int lo = 0, hi = 0;
        long long ans = 0;
        for (int i = n-1; i >= 0; i--) {
            while(lo < n && nums[i] + nums[lo] < lower) {
                lo++;
            } 
            while(hi < n && nums[i] + nums[hi] <= upper) {
                hi++;
            } 
            ans += hi - lo;
            if (lo <= i && i < hi) {
                ans--;
            }
        }
        return ans/2;
    }
};
