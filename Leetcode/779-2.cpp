class Solution {
public:
    int kthGrammar(int n, int k) {
        return __builtin_parity(k-1);
    }
};
