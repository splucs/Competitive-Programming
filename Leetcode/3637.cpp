class Solution {
public:
    bool isTrionic(vector<int>& nums) {
        if (nums[0] >= nums[1]) {
            return false;
        }
        int n = nums.size();
        bool goingUp = true;
        int changes = 0;
        for (int i = 1; i < n; i++) {
            if (nums[i-1] < nums[i]) {
                if (!goingUp) changes++;
                goingUp = true;
            } else if (nums[i-1] > nums[i]) {
                if (goingUp) changes++;
                goingUp = false;
            } else {
                return false;
            }
        }
        return changes == 2;
    }
};
