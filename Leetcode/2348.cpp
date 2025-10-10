class Solution {
public:
    long long zeroFilledSubarray(vector<int>& nums) {
        int numZeroes = 0;
        long long ans = 0;
        for (int num : nums) {
            if (num != 0) {
                numZeroes = 0;
            } else {
                numZeroes++;
                ans += numZeroes;
            }
        }
        return ans;
    }
};
