class Solution {
public:
    vector<int> sortArrayByParity(vector<int>& nums) {
        int i = 0, j = nums.size()-1;
        int tmp;
        while (i < j) {
            while (i < j && (nums[i]&1) == 0) i++;
            while (i < j && (nums[j]&1) != 0) j--;
            tmp = nums[i];
            nums[i] = nums[j];
            nums[j] = tmp;
        }
        return nums;
    }
};
