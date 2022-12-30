#include <bits/stdc++.h>
using namespace std;

struct node {
    node *l, *r;
    char name[6], lname[6], rname[6];
    char op;
    long long v;
    node(char line[]) : v(0), op(0), l(NULL), r(NULL) {
        line[4] = 0;
        sscanf(line, " %s", name);
        if (line[6] >= '0' && line[6] <= '9') {
            v = atoi(line+6);
            strcpy(lname, "");
            strcpy(rname, "");
        }
        else {
            sscanf(line+6, " %s %c %s", lname, &op, rname);
        }
    }
};

node *readInput() {
    char buf[100];
    map<string, node*> nodesByName;
    while(gets(buf)) {
        node *a = new node(buf);
        nodesByName[string(a->name)] = a;
    }

    map<string, int> used;
    for (pair<string, node*> entry : nodesByName) {
        node *a = entry.second;
        if (!a->op) {
            continue;
        }

        a->l = nodesByName[string(a->lname)];
        a->r = nodesByName[string(a->rname)];
    }
    return nodesByName["root"];
}

long long calculate(node *a) {
    if (!a->op) {
        return a->v;
    }
    
    long long vl = calculate(a->l);
    long long vr = calculate(a->r);

    switch (a->op) {
    case '+':
        return vl+vr;
    case '-':
        return vl-vr;
    case '*':
        return vl*vr;
    case '/':
        return vl/vr;
    }

    printf("found unknown operand %c\n", a->op);
    exit(1);
    return 0;
}

int main() {
    node *root = readInput();
    printf("%lld\n", calculate(root));
    return 0;
}