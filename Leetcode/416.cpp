class Solution {
private:
    vector<int> nums;
    vector<unordered_map<int, bool>> memo;
    bool recurse(int i, int bal) {
        if (i == (int)nums.size()) {
            return bal == 0;
        }
        if (memo[i].count(bal)) {
            return memo[i][bal];
        }
        int diff = nums[i];
        if (bal * diff > 0) { // small optimization
            diff = -diff;
        }
        bool ans = recurse(i+1, bal+diff) || recurse(i+1, bal-diff);
        memo[i][bal] = ans;
        return ans;
    }
public:
    bool canPartition(vector<int>& _nums) {
        nums.swap(_nums);
        memo.resize(nums.size());
        return recurse(0, 0);
    }
};
