class Solution {
public:
    int minOperations(vector<int>& nums, int k) {
        vector<bool> seen(101, false);
        int minNum = 100, unique = 0;
        for (int num : nums) {
            minNum = min(minNum, num);
            if (!seen[num]) {
                unique++;
                seen[num] = true;
            }
        }
        if (k > minNum) {
            return -1;
        }
        if (k < minNum) {
            return unique;
        }
        return unique-1;
    }
};
