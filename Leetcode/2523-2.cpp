#define INF 0x3f3f3f3f
class Solution {
private:
    int g(int p, int k) {
	    if (p == 1) return 1;
	    return (k==0) - (k==1);
    }
public:
    vector<int> closestPrimes(int left, int right) {
        vector<bool> isPrime(right+1, true);
        vector<int> primes, f(right+1), pw(right+1);
        int lastPrime = -1, minDist = INF;
        vector<int> ans = {-1, -1};
        isPrime[0] = isPrime[1] = false;
	    f[1] = g(1, 1);
	    for (int i = 2; i <= right; i++) {
		    if (isPrime[i]) {
			    primes.push_back(i);
			    f[i] = g(i, 1);
                pw[i] = 1;
            
                if (lastPrime >= left && i - lastPrime < minDist) {
                    minDist = i - lastPrime;
                    ans = {lastPrime, i};
                }
                lastPrime = i;
		    }

		    for (int j = 0; j < primes.size() && i*1ll*primes[j] <= right; j++) {
			    isPrime[i * primes[j]] = 0;
			    if (i % primes[j] == 0) {
				    int pwr = 1;
				    for(int k = 0; k < pw[i]; k++) pwr *= primes[j];
				    f[i * primes[j]] = f[i / pwr] * g(primes[j], pw[i]+1);
				    pw[i * primes[j]] = pw[i] + 1;
				    break;
			    }
				f[i * primes[j]] = f[i] * f[primes[j]];
				pw[i * primes[j]] = 1;
		    }
	    }
        return ans;
    }
};
