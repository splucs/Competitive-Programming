#include <bits/stdc++.h>
using namespace std;
#define MAXN 109

pair<string, string> operands[MAXN];
char op[MAXN];
int n;
deque<int> items[MAXN];
int divisible[MAXN], iftrue[MAXN], iffalse[MAXN];
int inspected[MAXN];

void readInput() {
    n = 0;
    int monkey;
    char line[MAXN], op1[MAXN], op2[MAXN];
    while(scanf(" Monkey %d: ", &monkey) != EOF) {
        n++;
        inspected[monkey] = 0;

        // Read starting items
        scanf(" Starting items: ");
        gets(line);
        int len = strlen(line);
        line[len++] = '\n';
        string cur;
        items[monkey].clear();
        for (int i = 0; i < len; i++) {
            char c = line[i];
            if (c == ' ' || c == '\n' || c == ',') {
                if (cur.size() > 0) {
                    int worry = atoi(cur.c_str());
                    items[monkey].push_back(worry);
                }
                cur.clear();
            }
            else {
                cur.push_back(c);
            }
        }

        // Read operation
        scanf(" Operation: new = %s %c %s", op1, &op[monkey], op2);
        operands[monkey] = pair<string,string>(string(op1), string(op2));

        // Read test
        scanf(" Test: divisible by %d", &divisible[monkey]);
        scanf(" If true: throw to monkey %d", &iftrue[monkey]);
        scanf(" If false: throw to monkey %d", &iffalse[monkey]);
    }
}

void printState() {
    for(int monkey = 0; monkey < n; monkey++) {
        printf("Monkey %d:", monkey);
        bool comma = false;
        for (int item : items[monkey]) {
            if (comma) {
                printf(",");
            }
            comma = true;
            printf(" %d", item);
        }
        printf("\n");
    }
    printf("\n");
}

int resolveOperand(string str, int worry) {
    if (str == "old") {
        return worry;
    }
    return atoi(str.c_str());
}

int doOp(int op1, char op, int op2) {
    switch (op)
    {
    case '+':
        return op1+op2;
    case '-':
        return op1-op2;
    case '*':
        return op1*op2;
    case '/':
        return op1/op2;
    default:
        printf("Found unknown operand %c\n", op);
        exit(1);
    }
    return 0;
}

void go() {
    for(int round = 1; round <= 20; round++) {
        for(int monkey = 0; monkey < n; monkey++) {
            while(!items[monkey].empty()) {
                inspected[monkey]++;
                int item = items[monkey].front();
                items[monkey].pop_front();

                // Monkey inspects
                int op1 = resolveOperand(operands[monkey].first, item);
                int op2 = resolveOperand(operands[monkey].second, item);
                item = doOp(op1, op[monkey], op2);

                // Monkey gets bored
                item /= 3;

                // Monkey throws
                int toThrow;
                if (item % divisible[monkey] == 0) {
                    toThrow = iftrue[monkey];
                }
                else {
                    toThrow = iffalse[monkey];
                }
                items[toThrow].push_back(item);
            }
        }
    }

    priority_queue<int> business;
    for(int monkey = 0; monkey < n; monkey++) {
        business.push(inspected[monkey]);
    }
    int monkeyBusiness = 1;
    for (int top = 0; top < 2; top++) {
        int topBusiness = business.top();
        business.pop();
        monkeyBusiness *= topBusiness;
    }
    printf("%d\n", monkeyBusiness);
}

int main() {
    readInput();
    printState();
    go();
}