class Solution {
private:
    vector<int> nums;
    vector<vector<int>> memo;
    bool recurse(int i, int bal) {
        if (bal < 0) {
            return false;
        }
        if (i == (int)nums.size()) {
            return bal == 0;
        }
        if (memo[i][bal] != 0) {
            return memo[i][bal] == 1;
        }
        bool ans = recurse(i+1, bal-nums[i]) || recurse(i+1, bal);
        memo[i][bal] = ans ? 1 : -1;
        return ans;
    }
public:
    bool canPartition(vector<int>& _nums) {
        nums.swap(_nums);
        int sum = 0;
        for (int num : nums) {
            sum += num;
        }
        if (sum & 1) {
            return false;
        }
        sum >>= 1;

        memo.assign(nums.size(), vector<int>(sum+1, 0));
        return recurse(0, sum);
    }
};
