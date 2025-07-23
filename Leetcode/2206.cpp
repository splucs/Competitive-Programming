class Solution {
public:
    bool divideArray(vector<int>& nums) {
        int maxElem = *max_element(nums.begin(), nums.end());
        vector<bool> parity(maxElem+1, 0);
        for (int num : nums) {
            parity[num] = !parity[num];
        }
        for (int i = 0; i < maxElem; i++) {
            if (parity[i]) {
                return false;
            }
        }
        return true;
    }
};
