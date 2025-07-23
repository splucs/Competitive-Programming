class Solution {
private:
    inline long long nextKMirror(long long x, int k) {
        vector<int> digits;
        for(; x > 0; x /= k) { 
            digits.push_back(x%k);
        }
        reverse(digits.begin(), digits.end());

        int n = digits.size(), midi = (n-1)/2, midj = n/2;
        for (int i = midi, j = midj; i >= 0; i--, j++) {
            if (digits[i] == digits[j]) {
                continue;
            }
            if (digits[i] > digits[j]) {
                break;
            }
            digits[midi]++;
            int carry = 0;
            for (int it = midi; it >= 0; it--) {
                digits[it] += carry;
                carry = digits[it]/k;
                digits[it] %= k;
            }
            break;
        }
        
        for (int i = 0, j = n-1; i < j; i++, j--) {
            digits[j] = digits[i];
        }
        long long ans = 0;
        for (int d : digits) {
            ans = ans*k + d;
        }
        return ans;
    }
public:
    long long kMirror(int k, int n) {
        long long cur = 1, nxt, ans = 0;
        while (n --> 0) {
            long long prev;
            do {
                prev = cur;
                cur = nextKMirror(nextKMirror(cur, 10), k);
            } while (cur != prev);
            ans += cur;
            cur++;
        }
        return ans;
    }
};
