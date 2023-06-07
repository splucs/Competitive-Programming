class Solution {
public:
    int minFlips(int a, int b, int c) {
        int ans = 0;
        while (a || b || c) {
            int aBit = a&1; a >>= 1;
            int bBit = b&1; b >>= 1;
            int cBit = c&1; c >>= 1;
            if (cBit) {
                if (!aBit && !bBit) ans++;
            } else {
                ans += aBit + bBit;
            }
        }
        return ans;
    }
};
