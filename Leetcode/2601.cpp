class Solution {
private:
    vector<int> primes;
    void sieve(int n) {
        vector<bool> isPrime(n, true);
        isPrime[0] = isPrime[1] = false;

        // Zero is not prime, but it's a valid substraction for this problem.
        primes.push_back(0);
        for (int i = 2; i < n; i++) {
            if (!isPrime[i]) {
                continue;
            }
            primes.push_back(i);
            for (int j = i+i; j < n; j += i) {
                isPrime[j] = false;
            }
        }
    }
public:
    bool primeSubOperation(vector<int>& nums) {
        sieve(*max_element(nums.begin(), nums.end()));

        int prev = 0;
        for (int x : nums) {
            int hi = primes.size();
            int lo = -1;
            while (hi > lo + 1) {
                int mid = (hi+lo)>>1;
                if (x - primes[mid] > prev) lo = mid;
                else hi = mid;
            }
            if (lo == -1) {
                return false;
            }
            prev = x - primes[lo];
        }

        return true;
    }
};
