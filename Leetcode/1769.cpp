class Solution {
public:
    vector<int> minOperations(string boxes) {
        int n = boxes.size();
        int cur = 0, balls = 0;
        for (int i = 0; i < n; i++) {
            if (boxes[i] == '1') {
                cur += i;
                balls++;
            }
        }

        vector<int> ans(n);
        int passed = 0;
        for (int i = 0; i < n; i++) {
            ans[i] = cur;
            if (boxes[i] == '1') {
                passed++;
            }
            cur -= balls - passed;
            cur += passed;
        }
        return ans;
    }
};
