class Solution {
public:
    int minSwaps(string s) {
        int bal = 0, minBal = 0;
        for (char c : s) {
            if (c == '[') {
                bal++;
            } else {
                bal--;
                minBal = min(minBal, bal);
            }
        }

        return (1-minBal)/2;
    }
};
