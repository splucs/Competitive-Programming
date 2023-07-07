class Solution {
public:
    int maxConsecutiveAnswers(string answerKey, int k) {
        int n = answerKey.size();
        int numTrue = 0, numFalse = 0;
        int ans = 0;
        for (int i = 0, j = 0; j < n; j++) {
            if (answerKey[j] == 'T') {
                numTrue++;
            } else {
                numFalse++;
            }

            while (numTrue > k && numFalse > k) {
                if (answerKey[i] == 'T') {
                    numTrue--;
                } else {
                    numFalse--;
                }
                i++;
            }

            int cur = j-i+1;
            if (ans < cur) ans = cur;
        }
        return ans;
    }
};
