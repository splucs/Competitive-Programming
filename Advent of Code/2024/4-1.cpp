#include <bits/stdc++.h>
using namespace std;

const string pattern = "XMAS";

vector<string> input;
int n, m;

void readInput() {
    string line;
    while(cin >> line) {
        input.push_back(line);
    }
    n = input.size();
    m = input[0].size();
}

int findPattern(int si, int sj, int di, int dj) {
    string line;
    int ans = 0;
    for (int i = si, j = sj; i >= 0 && j >= 0 && i < n && j < m; i += di, j += dj) {
        line.push_back(input[i][j]);
        if (line.size() >= 4 && line.substr(line.size()-4) == pattern) {
            ans++;
        }
    }
    return ans;
}

int main() {
    readInput();
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans += findPattern(i, 0, -1, 1);
        ans += findPattern(i, 0, 0, 1);
        ans += findPattern(i, 0, 1, 1);
        ans += findPattern(i, m-1, -1, -1);
        ans += findPattern(i, m-1, 0, -1);
        ans += findPattern(i, m-1, 1, -1);
    }
    for (int j = 0; j < m; j++) {
        ans += findPattern(0, j, 1, -1);
        ans += findPattern(0, j, 1, 0);
        ans += findPattern(0, j, 1, 1);
        ans += findPattern(n-1, j, -1, -1);
        ans += findPattern(n-1, j, -1, 0);
        ans += findPattern(n-1, j, -1, 1);
    }
    // diagonals are counted twice
    ans -= findPattern(0, 0, 1, 1);
    ans -= findPattern(0, m-1, 1, -1);
    ans -= findPattern(n-1, 0, -1, 1);
    ans -= findPattern(n-1, m-1, -1, -1);
    printf("%d\n", ans);
    return 0;
}
