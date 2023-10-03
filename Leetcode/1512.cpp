class Solution {
public:
    int numIdenticalPairs(vector<int>& nums) {
        vector<int> freq(101, 0);
        for (int num : nums) freq[num]++;
        int ans = 0;
        for (int f : freq) {
            if (f > 1) ans += (f*(f-1))>>1;
        }
        return ans;
    }
};
