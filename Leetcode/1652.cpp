class Solution {
public:
    vector<int> decrypt(vector<int>& code, int k) {
        if (k < 0) {
            reverse(code.begin(), code.end());
            code = decrypt(code, -k);
            reverse(code.begin(), code.end());
            return code;
        }

        int window = 0, n = code.size();
        for (int i = 0; i < k; i++) {
            window += code[i];
        }
        vector<int> ans(n);
        for (int i = n-1; i >= 0; i--) {
            ans[i] = window;
            window += code[i] - code[(i+k)%n];
        }
        return ans;
    }
};
