class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
        if (numerator == 0) {
            return "0";
        }

        string ans = "";
        long long num = numerator, den = denominator;

        bool isNegative = false;
        if (num < 0) {
            num = -num;
            isNegative = !isNegative;
        }
        if (den < 0) {
            den = -den;
            isNegative = !isNegative;
        }
        if (isNegative) {
            ans += "-";
        }

        ans += to_string(num/den);
        num %= den;
        if (num == 0) {
            return ans;
        }

        unordered_map<long long, int> seen;
        ans += ".";
        while (num > 0) {
            if (seen.count(num)) {
                ans.insert(seen[num], "(");
                ans += ")";
                break;
            }
            seen[num] = ans.size();
            num *= 10;
            ans += to_string(num/den);
            num %= den;
        }
        return ans;
    }
};
