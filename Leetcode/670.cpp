class Solution {
private:
    int pow[10] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
public:
    int maximumSwap(int num) {
        vector<int> digits;
        for (int x = num; x > 0; x /= 10) {
            digits.push_back(x%10);
        }

        int ans = num;
        for (int i = 0; i < (int)digits.size(); i++) {
            for (int j = 0; j < i; j++) {
                int cand = num;
                cand -= digits[i]*pow[i] + digits[j]*pow[j];
                cand += digits[i]*pow[j] + digits[j]*pow[i];
                ans = max(ans, cand);
            }
        }
        return ans;
    }
};
