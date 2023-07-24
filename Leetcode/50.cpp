class Solution {
public:
    double myPow(double x, int n) {
        double ans = 1;
        if (n < 0) {
            x = 1/x;
            // The only negative int that cannot be represented as positive
            if (n == -2147483648) {
                ans *= x;
                n++;
            }
            n = -n;
        }
        while (n) {
            if (n&1) ans *= x;
            n >>= 1;
            x = x*x;
        }
        return ans;
    }
};
