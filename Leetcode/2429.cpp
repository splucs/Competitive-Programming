class Solution {
public:
    int minimizeXor(int num1, int num2) {
        int numBits = __builtin_popcount(num2);
        int x = 0;
        for (int i = 30; i >= 0 && numBits > 0; i--) {
            if (num1 & (1<<i)) {
                x |= (1<<i);
                numBits--;
            }
        }
        for (int i = 0; i < 31 && numBits > 0; i++) {
            if (!(num1 & (1<<i))) {
                x |= (1<<i);
                numBits--;
            }
        }
        return x;
    }
};
