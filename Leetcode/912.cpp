class Solution {
private:
    vector<int> nums;
    void quick(int l, int r) {
        if (r-l <= 1) {
            return;
        }

        int pivot = nums[(rand() % (r-l)) + l];
        // Build a tri-partition:
        // - [l, eq): < pivot
        // - [eq, ge): == pivot
        // - [ge, r): > pivot
        int eq = l, ge = l;
        for (int i = l; i < r; i++) {
            if (nums[i] < pivot) {
                swap(nums[i], nums[ge]);
                swap(nums[eq++], nums[ge++]);
            } else if (nums[i] == pivot) {
                swap(nums[i], nums[ge++]);
            }
        }
        
        quick(l, eq);
        quick(ge, r);
    }
public:
    vector<int> sortArray(vector<int>& _nums) {
        nums.swap(_nums);
        quick(0, nums.size());
        return nums;
    }
};
