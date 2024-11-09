class Solution {
public:
    bool canSortArray(vector<int>& nums) {
        int lastBits = __builtin_popcount(nums[0]), lastIdx = 0;
        for (int i = 1; i < (int)nums.size(); i++) {
            int bits = __builtin_popcount(nums[i]);
            if (bits != lastBits) {
                sort(nums.begin()+lastIdx, nums.begin()+i);
                lastBits = bits;
                lastIdx = i;
            }
        }
        sort(nums.begin()+lastIdx, nums.end());

        for (int i = 1; i < (int)nums.size(); i++) {
            if (nums[i] < nums[i-1]) {
                return false;
            }
        }
        return true;
    }
};

