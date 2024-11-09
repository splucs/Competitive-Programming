class Solution {
public:
    int minAddToMakeValid(string s) {
        int bal = 0, ans = 0;
        for (char c : s) {
            if (c == '(') {
                bal++;
            } else {
                bal--;
                if (bal < 0) {
                    bal++;
                    ans++;
                }
            }
        }
        return ans + bal;
    }
};
