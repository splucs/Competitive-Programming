#define MAX_BITS 18

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int n = nums.size()-1;
        
        int correctBits[MAX_BITS];
        for (int b = 0; b < MAX_BITS; b++) {
            int &bits = correctBits[b];
            bits = 0;
            for (int i = 1; i <= n; i++) {
                if (i & (1<<b)) bits++;
            }
        }

        int numsBits[MAX_BITS];
        for (int b = 0; b < MAX_BITS; b++) {
            int &bits = numsBits[b];
            bits = 0;
            for (int i : nums) {
                if (i & (1<<b)) bits++;
            }
        }

        int ans = 0;
        for (int b = 0; b < MAX_BITS; b++) {
            if (correctBits[b] < numsBits[b]) ans |= (1<<b);
        }
        return ans;
    }
};
