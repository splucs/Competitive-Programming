class Solution {
    unordered_set<long long> seen;

    inline long long encode(const vector<int> &freq) {
        long long code = 0;
        for (int i = 0; i < 10; i++) {
            code = code*10 + freq[i];
        }
        return code;
    }

    inline long long countGood(long long x) {
        vector<int> freq(10, 0);
        for (; x > 0; x /= 10) {
            freq[x%10]++;
        }

        long long code = encode(freq);
        if (seen.count(code)) {
            return 0;
        }
        seen.insert(code);

        long long ans = 0;
        for (int firstDigit = 1; firstDigit < 10; firstDigit++) {
            if (freq[firstDigit] == 0) continue;
            freq[firstDigit]--;
            long long curAns = 1, num = 1;
            for (int i = 0; i < 10; i++) {
                for (int den = 1; den <= freq[i]; den++) {
                    curAns *= num++;
                    curAns /= den;
                }
            }
            ans += curAns;
            freq[firstDigit]++;
        }
        return ans;
    }

    inline long long reverse(long long x) {
        long long ans = 0;
        for (; x > 0; x /= 10) {
            ans = ans*10 + x%10;
        }
        return ans;
    }
public:
    long long countGoodIntegers(int n, int k) {
        if (n == 1) {
            return 9/k;
        }

        long long powHalf = 1;
        for (int i = 0; i < n/2; i++) powHalf *= 10;

        long long ans = 0;
        for (long long upper = powHalf/10; upper < powHalf; upper++) {
            long long lower = reverse(upper);
            if (n & 1) {
                for (int mid = 0; mid < 10; mid++) {
                    long long x = upper*powHalf*10 + mid*powHalf + lower;
                    if (x % k == 0) {
                        ans += countGood(x);
                    }
                }
            } else {
                long long x = upper*powHalf + lower;
                if (x % k == 0) {
                    ans += countGood(x);
                }
            }
        }
        return ans;
    }
};
