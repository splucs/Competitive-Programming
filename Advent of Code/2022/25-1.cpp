#include <bits/stdc++.h>
using namespace std;

long long fromSnafu(string snafu) {
    int n = snafu.size();
    long long p = 1;
    long long ans = 0;
    for (int i = n-1; i >= 0; i--) {
        char c = snafu[i];
        if (c >= '0' && c <= '9') {
            ans += (c-'0')*p;
        }
        else if (c == '-') {
            ans -= p;
        }
        else if (c == '=') {
            ans -= 2*p;
        }

        p *= 5;
    }
    return ans;
}

string toSnafu(long long num) {
    string snafu;
    while(num > 0) {
        int alg = num%5;
        num /= 5;
        if (alg > 2) {
            alg -= 5;
            num++;
        }

        if (alg >= 0) snafu.push_back(alg+'0');
        else if (alg == -1) snafu.push_back('-');
        else if (alg == -2) snafu.push_back('=');
    }

    if (snafu.empty()) {
        snafu.push_back('0');
    }

    reverse(snafu.begin(), snafu.end());
    return snafu;
}

int main() {
    char snafu[109];
    long long ans = 0;
    while(scanf(" %s", snafu) != EOF) {
        ans += fromSnafu(string(snafu));
    }
    printf("%s\n", toSnafu(ans).c_str());
    return 0;
}