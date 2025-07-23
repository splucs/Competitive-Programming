class Solution {
public:
    bool isZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        vector<int> diff(nums.size()+1, 0);
        for (const vector<int>& query : queries) {
            int i = query[0], j = query[1];
            diff[i]++;
            diff[j+1]--;
        }
        int sum = 0;
        for (int i = 0; i < (int)nums.size(); i++) {
            sum += diff[i];
            if (sum < nums[i]) {
                return false;
            }
        }
        return true;
    }
};
