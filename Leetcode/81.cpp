class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        int tail = findTail(nums);
        if (tail == -1) {
            for (int i = 0; i < n; i++) {
                if (nums[i] == target) return true;
            }
            return false;
        }

        int offset = findRotatedStart(nums, tail); 
        int lo = 0, hi = n;
        while(hi > lo+1) {
            int mid = (hi+lo)>>1;
            if (nums[(mid+offset)%n] <= target) lo = mid;
            else hi = mid;
        }

        int ans = (lo+offset)%n;
        return nums[ans] == target;
    }
    int findRotatedStart(vector<int>& nums, int tail) {
        int n = nums.size();
        int lo = 0, hi = tail+1;
        while(hi > lo+1) {
            int mid = (hi+lo)>>1;
            if (nums[mid] >= nums[0]) lo = mid;
            else hi = mid;
        }
        return hi%n;
    }
    // try to find latest index i such that nums[i] != nums[0]
    int findTail(vector<int>& nums) {
        int lo = 0, hi = nums.size();
        while (hi > lo+1) {
            int mid = (hi+lo)>>1;
            if (nums[0] == nums[mid]) hi = mid;
            else lo = mid;
        }
        if (lo == 0) return -1;
        return lo;
    }
};
