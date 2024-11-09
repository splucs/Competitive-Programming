long long gcd(long long a, long long b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a%b);
}

long long abso(long long a) {
    return a > 0 ? a : -a;
}

struct fraction {
    long long num, den;
    fraction() : num(0), den(0) {}
    fraction(long long _num, long long _den) : num(_num), den(_den) {}
    fraction reduce() {
        long long g = gcd(abso(num), abso(den));
        return fraction(num/g, den/g);
    }
};

fraction operator +(const fraction& a, const fraction& b) {
    return fraction(a.num*b.den + b.num*a.den, a.den*b.den).reduce();
}

class Solution {
public:
    string fractionAddition(string expression) {
        vector<fraction> fractions;
        fraction cur;
        bool negative = false;
        long long curNum = 0;
        for (char c : expression) {
            if (c >= '0' && c <= '9') {
                curNum = 10*curNum + c - '0';
            } else if (c == '/') {
                cur.num = negative ? -curNum : curNum;
                curNum = 0;
            } else if (c == '+' || c == '-') {
                if (curNum > 0) {
                    cur.den = curNum;
                    curNum = 0;
                    fractions.push_back(cur);
                    cur = fraction();
                }
                negative = c == '-';
            }
        }
        cur.den = curNum;
        fractions.push_back(cur);

        fraction ans(0, 1);
        for (fraction &f : fractions) {
            ans = ans + f;
        }
        return to_string(ans.num) + "/" + to_string(ans.den);
    }
};
