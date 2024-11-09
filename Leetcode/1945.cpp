class Solution {
private:
    int sumOfDigits(int x) {
        int ans = 0;
        for (; x > 0; x /= 10) {
            ans += x%10;
        }
        return ans;
    }
public:
    int getLucky(string s, int k) {
        int ans = 0;
        for (char c : s) {
            ans += sumOfDigits(c - 'a' + 1);
        }
        for (int t = 1; t < k; t++) {
            ans = sumOfDigits(ans);
        }
        return ans;
    }
};
