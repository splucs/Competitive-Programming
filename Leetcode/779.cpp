class Solution {
public:
    int kthGrammar(int n, int k) {
        n--; k--;

        int bit = 0;
        for (int i = n-1; i >= 0; i--) {
            if (k & (1<<i)) bit ^= 1;
        }
        return bit;
    }
};
