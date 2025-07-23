class Solution {
private:
    int lower_bound(vector<int>& nums, int val) {
        int lo = -1, hi = nums.size();
        while(hi > lo + 1) {
            int mid = (hi+lo)>>1;
            if (nums[mid] < val) lo = mid;
            else hi = mid;
        }
        return hi;
    }
public:
    int maximumCount(vector<int>& nums) {
        int pos = nums.size() - lower_bound(nums, 1);
        int neg = lower_bound(nums, 0);
        return max(pos, neg);
    }
};
