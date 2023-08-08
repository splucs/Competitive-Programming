class Solution {
public:
    int search(vector<int>& nums, int target) {
        int offset = findRotatedStart(nums); 

        int n = nums.size();
        int lo = 0, hi = n;
        while(hi > lo+1) {
            int mid = (hi+lo)>>1;
            if (nums[(mid+offset)%n] <= target) lo = mid;
            else hi = mid;
        }

        int ans = (lo+offset)%n;
        if (nums[ans] != target) return -1;
        return ans;
    }
    int findRotatedStart(vector<int>& nums) {
        int n = nums.size();
        int lo = 0, hi = n;
        while(hi > lo+1) {
            int mid = (hi+lo)>>1;
            if (nums[mid] > nums[0]) lo = mid;
            else hi = mid;
        }
        return hi%n;
    }
};
