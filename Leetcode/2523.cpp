#define INF 0x3f3f3f3f
class Solution {
public:
    vector<int> closestPrimes(int left, int right) {
        vector<bool> isPrime(right+1, true);
        isPrime[1] = false;
        int lastPrime = -1, minDist = INF;
        vector<int> ans = {-1, -1};
        for (int i = 2; i <= right; i++) {
            if (!isPrime[i]) {
                continue;
            }
            for (int j = i+i; j <= right; j += i) {
                isPrime[j] = false;
            }

            if (lastPrime >= left && i - lastPrime < minDist) {
                minDist = i - lastPrime;
                ans = {lastPrime, i};
            }
            lastPrime = i;
        }
        return ans;
    }
};
