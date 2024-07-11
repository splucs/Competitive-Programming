class Solution {
private:
    inline int mod(int i, int n) {
        return (i-1)%n + 1;
    }
public:
    int findTheWinner(int n, int k) {
        int ans = 1;
        for (int i = 2; i <= n; i++) {
            ans = mod(ans + mod(k, i), i);
        }
        return ans;
    }
};
