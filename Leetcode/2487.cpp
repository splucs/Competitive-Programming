class Solution {
public:
    int maxSum(vector<int>& nums) {
        vector<bool> seen(101, false);
        int maxSeen = -101;
        int selected = 0;
        int sum = 0;
        for (int num : nums) {
            maxSeen = max(maxSeen, num);
            if (num < 0 || seen[num]) {
                continue;
            }
            seen[num] = true;
            selected++;
            sum += num;
        }
        if (selected == 0) {
            return maxSeen;
        }
        return sum;
    }
};
