#define MAX_DIGIT 17
class Solution {
public:
    long long numberOfPowerfulInt(long long start, long long finish, int limit, string s) {
        vector<int> startDigits(MAX_DIGIT);
        for (int i = 0; i < MAX_DIGIT; i++) {
            startDigits[i] = start%10;
            start /= 10;
        }
        vector<int> finishDigits(MAX_DIGIT);
        for (int i = 0; i < MAX_DIGIT; i++) {
            finishDigits[i] = finish%10;
            finish /= 10;
        }
        vector<int> suffixDigits(MAX_DIGIT);
        reverse(s.begin(), s.end());
        for (int i = 0; i < MAX_DIGIT; i++) {
            suffixDigits[i] = i < s.size() ? s[i]-'0' : 0;
        }

        // dp[i][lo][hi] = result for digit i onwards, lo = whether bound by start, hi = whether bound by finish
        vector<vector<vector<long long>>> dp(MAX_DIGIT, vector<vector<long long>>(2, vector<long long>(2, 0)));
        for (int i = 0; i < MAX_DIGIT; i++) {
            for (int lo = 0; lo < 2; lo++) for (int hi = 0; hi < 2; hi++) {
                int st = 0;
                if (lo == 1) st = max(st, startDigits[i]);
                if (i < s.size()) st = max(st, suffixDigits[i]);
                int en = limit;
                if (hi == 1) en = min(en, finishDigits[i]);
                if (i < s.size()) en = min(en, suffixDigits[i]);

                long long &ans = dp[i][lo][hi];
                for (int d = st; d <= en; d++) {
                    if (i == 0) {
                        ans++;
                        continue;
                    }
                    int newLo = lo == 1 && d == startDigits[i] ? 1 : 0;
                    int newHi = hi == 1 && d == finishDigits[i] ? 1 : 0;
                    ans += dp[i-1][newLo][newHi];
                }
            }
        }
        return dp[MAX_DIGIT-1][1][1];
    }
};
