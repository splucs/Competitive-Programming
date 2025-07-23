class Solution {
private:
    int k, ans;
    vector<int> digits;
    // state = 0: current is a prefix of digits
    // state = 1: current is a prefix of digits and a bigger number
    // state = 2: current is a prefix of digits and a smaller number
    vector<vector<int>> memo;

    vector<int> currentPrefix;
    void find(int state) {
        if (currentPrefix.size() == digits.size() && state == 1) {
            return;
        }
        if (currentPrefix.size() > digits.size()) {
            return;
        }

        if (memo[currentPrefix.size()][state] != -1 && k > memo[currentPrefix.size()][state]) {
            k -= memo[currentPrefix.size()][state];
            return;
        }
        int initialK = k;

        if (!currentPrefix.empty()) {
            k--;
        }
        if (k == 0) {
            ans = 0;
            for (int d : currentPrefix) {
                ans = 10*ans + d;
            }
            return;
        }

        int pos = currentPrefix.size();
        for (int i = currentPrefix.empty() ? 1 : 0; i < 10 && k > 0 && pos < digits.size(); i++) {
            currentPrefix.push_back(i);
            int nstate = state;
            if (state == 0 && i > digits[pos]) {
                nstate = 1;
            }
            if (state == 0 && i < digits[pos]) {
                nstate = 2;
            }
            find(nstate);
            currentPrefix.pop_back();
        }

        memo[currentPrefix.size()][state] = initialK - k;
    }
public:
    int findKthNumber(int n, int _k) {
        k = _k;
        while (n > 0) {
            digits.push_back(n%10);
            n /= 10;
        }
        reverse(digits.begin(), digits.end());
        
        memo.assign(30, vector<int>(3, -1));
        find(0);
        return ans;
    }
};
