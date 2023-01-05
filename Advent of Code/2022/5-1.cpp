#include <bits/stdc++.h>
using namespace std;
#define MAXN 109

int main() {
    char line[MAXN];
    deque<char> stacks[12];
    int numStacks = 0;
    while(gets(line)) {
        if (line[1] == '1') {
            numStacks = line[strlen(line)-2]-'0';
            break;
        }
        int n = (strlen(line)+1)/4;
        for (int i = 0; i < n; i++) {
            char c = line[1+4*i];
            if (c == ' ') {
                continue;
            }
            stacks[i+1].push_front(c);
        }
    }

    int cnt, from, to;
    while(scanf(" move %d from %d to %d", &cnt, &from, &to) != EOF) {
        while (cnt --> 0) {
            stacks[to].push_back(stacks[from].back());
            stacks[from].pop_back();
        }
    }
    for (int s = 1; s <= numStacks; s++) {
        printf("%c", stacks[s].back());
    }
    printf("\n");
    return 0;
}