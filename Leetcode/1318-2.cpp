class Solution {
public:
    int minFlips(int a, int b, int c) {
        int curOr = a|b;
        int badOnes = curOr&(~c);
        int badZeroes = (~curOr)&c;
        return __builtin_popcount(badZeroes) + __builtin_popcount(badOnes&a) + __builtin_popcount(badOnes&b);
    }
};
