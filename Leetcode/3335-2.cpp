#define MOD 1000000007

typedef vector<vector<int>> matrix;

matrix zeroes(int n, int m) {
    return vector<vector<int>>(n, vector<int>(m, 0));
}

matrix mult(const matrix &a, const matrix &b) {
    int n = a.size(), m = b.size(), o = b[0].size();
    matrix c = zeroes(n, o);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < o; j++) {
            for (int k = 0; k < m; k++) {
                c[i][j] = (c[i][j] + (a[i][k]*(long long)b[k][j]) % MOD) % MOD;
            }
        }
    }
    return c;
}

class Solution {
public:
    int lengthAfterTransformations(string s, int t) {
        matrix freq = zeroes(26, 1);
        for (char c : s) {
            freq[c-'a'][0]++;
        }

        matrix base = zeroes(26, 26);
        base[0][25] = 1;
        base[1][25] = 1;
        for (int i = 1; i < 26; i++) {
            base[i][i-1]++;
        }

        for (; t > 0; t >>= 1) {
            if (t & 1) {
                freq = mult(base, freq);
            }
            base = mult(base, base);
        }
        int ans = 0;
        for (int i = 0; i < 26; i++) {
            ans = (ans + freq[i][0]) % MOD;
        }
        return ans;
    }
};
