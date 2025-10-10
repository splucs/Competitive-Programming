#include <bits/stdc++.h>
using namespace std;

const vector<vector<string>> patterns = {
    {
        {"S.S"},
        {".A."},
        {"M.M"}
    },
    {
        {"M.S"},
        {".A."},
        {"M.S"}
    },
    {
        {"M.M"},
        {".A."},
        {"S.S"}
    },
    {
        {"S.M"},
        {".A."},
        {"S.M"}
    }
};

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

int findPatterns() {
    int ans = 0;
    for (int i = 0; i < n-2; i++) for (int j = 0; j < m-2; j++) {
        for (int p = 0; p < (int)patterns.size(); p++) {
            bool found = true;
            for (int di = 0; di < 3 && found; di++) for (int dj = 0; dj < 3 && found; dj++) {
                if (patterns[p][di][dj] != '.' && patterns[p][di][dj] != input[i+di][j+dj]) {
                    found = false;
                }
            }
            if (found) {
                ans++;
            }
        }
    }
    return ans;
}

int main() {
    readInput();
    int ans = findPatterns();
    printf("%d\n", ans);
    return 0;
}
