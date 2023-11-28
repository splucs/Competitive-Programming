#define MOD 1000000007

class Solution {
public:
    int numberOfWays(string corridor) {
        int seats = 0, plants = 0;
        int ans = 1;
        for (char c : corridor) {
            if (c == 'S') {
                if ((seats & 1) == 0 && seats > 0) {
                    ans = (ans*1ll*(plants+1)) % MOD;
                }
                seats++;
                plants = 0;
            } else {
                plants++;
            }
        }
        if ((seats & 1) == 1 || seats == 0) {
            ans = 0;
        }
        return ans;
    }
};
