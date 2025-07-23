class Solution {
public:
    int minMaxDifference(int num) {
        int p = 1, lastNonOne = 0, lastNonZero = 0;
        int inc[10], dec[10];
        memset(&inc, 0, sizeof inc);
        memset(&dec, 0, sizeof dec);
        for(; num > 0; num /= 10, p *= 10) {
            int d = num%10;
            inc[d] += (9-d)*p;
            dec[d] += d*p;
        }
        int maxInc = 0, maxDec = 0;
        for (int i = 0; i < 10; i++) {
            maxInc = max(maxInc, inc[i]);
            maxDec = max(maxDec, dec[i]);
        }
        return maxInc + maxDec;
    }
};
