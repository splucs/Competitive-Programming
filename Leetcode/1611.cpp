class Solution {
public:
    int minimumOneBitOperations(int n) {
        bool flipped = false;
        int ans = 0;
        for (int i = (1<<30); i > 0; i >>= 1) {
            if (flipped == ((n&i) == 0)) {
                ans += i;
            }
            if (n&i) {
                flipped = !flipped;
            }
        }
        return ans;
    }
};
