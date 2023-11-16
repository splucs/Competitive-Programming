class Solution {
public:
    string findDifferentBinaryString(vector<string>& nums) {
        int n = nums.size();
        string ans(n, '0');
        for (int i = 0; i < n; i++) {
            if (nums[i][i] == '0') {
                ans[i] = '1';
            }
        }
        return ans;
    }
};
