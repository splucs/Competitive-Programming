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

map<string, node*> nodesByName;
node *root;

void readInput() {
    char buf[100];
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
    root = nodesByName["root"];
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

set<string> pathToHumn;

bool findPathToHumn(node *a) {
    if (!strcmp(a->name, "humn")) {
        pathToHumn.insert(a->name);
        return true;
    }
    if (!a->op) {
        return false;
    }
    if (findPathToHumn(a->l) || findPathToHumn(a->r)) {
        pathToHumn.insert(a->name);
        return true;
    }
    return false;
}

long long needsToEqual(node *a, long long v) {
    if (!strcmp(a->name, "humn")) {
        return v;
    }
    
    if (pathToHumn.count(a->r->name)) {
        long long vl = calculate(a->l);
        switch (a->op) {
        case '+':
            return needsToEqual(a->r, v-vl); // l+r=v => r=v-l
        case '-':
            return needsToEqual(a->r, vl-v); // l-r=v => r=l-v
        case '*':
            return needsToEqual(a->r, v/vl); // l*r=v => r=v/l
        case '/':
            return needsToEqual(a->r, vl/v); // l/r=v => r=l/v
        }
        printf("found unknown operand %c\n", a->op);
        exit(1);
        return 0;
    }
    else {
        long long vr = calculate(a->r);
        switch (a->op) {
        case '+':
            return needsToEqual(a->l, v-vr); // l+r=v => l=v-r
        case '-':
            return needsToEqual(a->l, v+vr); // l-r=v => l=v+r
        case '*':
            return needsToEqual(a->l, v/vr); // l*r=v => l=v/r
        case '/':
            return needsToEqual(a->l, v*vr); // l/r=v => l=v*r
        }
        printf("found unknown operand %c\n", a->op);
        exit(1);
        return 0;
    }

}

int main() {
    readInput();

    findPathToHumn(root);
    
    root->op = '-';
    long long ans = needsToEqual(root, 0);
    nodesByName["humn"]->v = ans;

    printf("%lld\n", ans);
    return 0;
}