class Solution {
public:
    bool isPowerOfThree(int n) {
        if (n <= 0) {
            return false;
        }
        for (; n > 1; n /= 3) {
            if (n % 3 != 0) {
                return false;
            }
        }
        return true;
    }
};
