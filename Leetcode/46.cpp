class Solution {
private:
    vector<vector<int>> ans;
public:
    vector<vector<int>> permute(vector<int>& nums) {
        ans.clear();
        recurse(nums, 0);
        return ans;
    }
    void recurse(vector<int>& nums, int i) {
        if (i == (int)nums.size()) {
            ans.push_back(nums);
            return;
        }
        for (int j = i; j < (int)nums.size(); j++) {
            swap(nums[i], nums[j]);
            recurse(nums, i+1);
            swap(nums[i], nums[j]);
        }
    }
};
