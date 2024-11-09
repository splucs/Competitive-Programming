class Solution {
public:
    long long minEnd(int n, int x) {
        long long ans = x, pow = 1;
        for (int last = n-1; last > 0; last >>= 1, pow <<= 1) {
            while (x & pow) {
                pow <<= 1;
            }
            if (last & 1) {
                ans |= pow;
            }
        }
        return ans;
    }
};
