class Solution {
public:
    int findComplement(int num) {
        unsigned int uNum = num;
        unsigned int n = 1;
        for (; uNum >= n; n <<= 1);
        return int((n-1)^uNum);
    }
};
