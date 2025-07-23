class Solution {
private:
    inline int digitSum(long long x) {
        int ans = 0;
        for (; x > 0; x /= 10) {
            ans += x%10;
        }
        return ans;
    }
public:
    long long makeIntegerBeautiful(long long n, int target) {
        long long x = 0;
        for (long long sum = n, pow = 1; sum > 0; pow *= 10, sum /= 10) {
            if (digitSum(n+x) <= target) {
                return x;
            }

            int digit = sum%10;
            int toAdd = (10 - digit) % 10;
            sum += toAdd;
            x += toAdd*pow;
        }
        return x;
    }
};
