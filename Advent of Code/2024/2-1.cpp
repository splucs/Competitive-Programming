#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> reports;

inline int abs(int x) {
    return x < 0 ? -x : x;
}

void readInput() {
    char buffer[109];
    while (gets(buffer) != NULL) {
        int n = strlen(buffer), x;
        vector<int> report;
        for (int i = 0, di; i < n; i += di) {
            sscanf(buffer+i, " %d%n", &x, &di);
            report.push_back(x);
        }
        reports.push_back(report);
    }
}

bool isSafe(vector<int>& report) {
    int n = report.size();
    bool isDecreasing = true, isIncreasing = true;
    for (int i = 1; i < n && (isIncreasing || isDecreasing); i++) {
        if (report[i-1] <= report[i]) {
            isDecreasing = false;
        }
        if (report[i-1] >= report[i]) {
            isIncreasing = false;
        }
        if (abs(report[i-1] - report[i]) > 3) {
            return false;
        }
    }
    return isIncreasing || isDecreasing;
}

int main() {
    readInput();

    int ans = 0;
    for (int i = 0; i < (int)reports.size(); i++) {
        if (isSafe(reports[i])) {
            ans++;
        }
    }
    printf("%d\n", ans);
    return 0;
}
