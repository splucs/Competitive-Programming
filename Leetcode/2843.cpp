class Solution {
public:
    int countSymmetricIntegers(int low, int high) {
        int ans = 0;
        for (int i = 11; i < 100; i += 11) {
            if (low <= i && i <= high) {
                ans++;
            }
        }
        for (int upper = 10; upper < 100; upper++) {
            int sum = (upper/10) + (upper%10);
            for (int c = max(0, sum-9); c < 10 && c <= sum; c++) {
                int d = sum-c;
                int i = upper*100 + c*10 + d;
                if (low <= i && i <= high) {
                    ans++;
                }
            }
        }
        return ans;
    }
};
