#define MOD 1000000007LL

template <typename T>
T extGcd(T a, T b, T& x, T& y) {
	if (b == 0) {
		x = 1; y = 0;
		return a;
	}
	else {
		T g = extGcd(b, a % b, y, x);
		y -= a / b * x;
		return g;
	}
}
 
template <typename T>
T modInv(T a, T m) {
	T x, y;
	extGcd(a, m, x, y);
	return (x % m + m) % m;
}

class Solution {
private:
    vector<long long> facCache;
    long long fac(int i) {
        while(i >= (int)facCache.size()) {
            int j = facCache.size();
            facCache.push_back((j * facCache[j-1]) % MOD);
        }
        return facCache[i];
    }

    long long anagrams(const vector<int>& freq) {
        int tot = 0, ans = 1;
        for (int f : freq) {
            tot += f;
            ans = (ans*modInv(fac(f), MOD)) % MOD;
        }
        ans = (ans*fac(tot)) % MOD;
        return ans;
    }
public:
    int countAnagrams(string s) {
        facCache.push_back(1);
        vector<int> freq(26, 0);
        int ans = 1;
        for (char c : s) {
            if (c == ' ') {
                ans = (ans*anagrams(freq)) % MOD;
                freq.assign(26, 0);
            } else {
                freq[c-'a']++;
            }
        }
        ans = (ans*anagrams(freq)) % MOD;
        return ans;
    }
};
