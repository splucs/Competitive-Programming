class Solution {
public:
    double myPow(double x, int n) {
        double ans = 1;
        unsigned int exp;
        if (n < 0) {
            x = 1/x;
            exp = -((long long)n);
        } else {
            exp = n;
        }
        while (exp) {
            if (exp&1) ans *= x;
            exp >>= 1;
            x = x*x;
        }
        return ans;
    }
};
