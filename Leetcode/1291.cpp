class Solution {
private:
    int numLen(int x) {
        int ans = 0;
        while(x > 0) {
            ans++;
            x /= 10;
        }
        return ans;
    }
public:
    vector<int> sequentialDigits(int low, int high) {
        vector<int> ans;

        int lenLow = numLen(low), lenHigh = numLen(high); 
        for (int len = 1; len <= 9; len++) {
            if (len < lenLow) continue;
            if (len > lenHigh) break;

            for (int offset = 1; offset <= 10-len; offset++) {
                int x = offset;
                for (int i = 1; i < len; i++) {
                    x = x*10 + i + offset;
                }
                if (x < low) continue;
                if (x > high) break;

                ans.push_back(x);
            }
        }

        return ans;
    }
};
