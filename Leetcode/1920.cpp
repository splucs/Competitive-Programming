#define MOD 1001
class Solution {
public:
    vector<int> buildArray(vector<int>& nums) {
        for (int& num : nums) {
            num = MOD*(nums[num] % MOD) + num;
        }
        for (int& num : nums) {
            num /= MOD;
        }
        return nums;
    }
};
