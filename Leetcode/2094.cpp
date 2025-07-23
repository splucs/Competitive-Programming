class Solution {
public:
    vector<int> findEvenNumbers(vector<int>& digits) {
        set<int> ans;
        int n = digits.size();
        for (int i = 0; i < n; i++) {
            if (digits[i] & 1) {
                continue;
            }
            for (int j = 0; j < n; j++) {
                if (j == i) {
                    continue;
                }
                for (int k = 0; k < n; k++) {
                    if (k == j || k == i) {
                        continue;
                    }
                    if (digits[k] == 0) {
                        continue;
                    }
                    ans.insert(digits[k]*100 + digits[j]*10 + digits[i]);
                }
            }
        }
        return vector<int>(ans.begin(), ans.end());
    }
};

