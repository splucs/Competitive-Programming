class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        int cnt5 = 0, cnt10 = 0;
        for (int bill : bills) {
            if (bill == 5) {
                cnt5++;
            } else if (bill == 10) {
                if (cnt5 == 0) {
                    return false;
                }
                cnt5--;
                cnt10++;
            } else if (bill == 20) {
                if (cnt10 > 0 && cnt5 > 0) {
                    cnt10--;
                    cnt5--;
                } else if (cnt5 >= 3) {
                    cnt5 -= 3;
                } else {
                    return false;
                }
            }
        }
        return true;
    }
};
