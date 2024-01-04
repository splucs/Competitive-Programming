class Solution {
public:
    int minOperations(vector<int>& nums) {
        int minNum = 1e7;
        int maxNum = 0;
        for (int num : nums) {
            minNum = min(minNum, num);
            maxNum = max(maxNum, num);
        }
        vector<int> bucket(maxNum-minNum+1, 0);
        for (int num : nums) {
            bucket[num-minNum]++;
        }
        int ans = 0;
        for (int v : bucket) {
            if (v == 1) {
                return -1;
            }
            ans += (v+2)/3;
        }
        return ans;
    }
};
