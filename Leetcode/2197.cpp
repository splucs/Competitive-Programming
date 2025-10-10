class Solution {
private:
    int gcd(int x, int y) {
        return y == 0 ? x : gcd(y, x%y);
    }
public:
    vector<int> replaceNonCoprimes(vector<int>& nums) {
        int stackPtr = 0, n = nums.size();
        for (int i = 0; i < n; i++) {
            int x = nums[i];
            while (stackPtr > 0) {
                int y = nums[stackPtr-1]; 
                int g = gcd(x, y);
                if (g == 1) {
                    break;
                }

                stackPtr--;
                x /= g;
                x *= y;
            }
            nums[stackPtr++] = x;
        }
        nums.resize(stackPtr);
        return nums;
    }
};
