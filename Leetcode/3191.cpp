class Solution {
public:
    int minOperations(vector<int>& nums) {
        int ans = 0, n = nums.size();
        for (int i = 0; i < n; i++) {
            if (nums[i] == 1) {
                continue;
            }
            ans++;
            for (int j = 0; j < 3; j++) {
                if (i+j >= n) {
                    return -1;
                }
                nums[i+j] = 1 - nums[i+j];
            }
        }
        return ans;
    }
};
