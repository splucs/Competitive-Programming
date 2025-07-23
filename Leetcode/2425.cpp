class Solution {
public:
    int xorAllNums(vector<int>& nums1, vector<int>& nums2) {
        int ans = 0;
        if (nums1.size() & 1) {
            for (int num : nums2) {
                ans ^= num;
            }
        }
        if (nums2.size() & 1) {
            for (int num : nums1) {
                ans ^= num;
            }
        }
        return ans;
    }
};
