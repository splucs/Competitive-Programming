#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009

struct node {
    vector<node*> sons;
    int value;
    bool isValue;
    node() : sons(vector<node*>()), isValue(false) {}
    node(int v) : value(v), isValue(true) {}
    ~node() {
        for (node* item : sons) {
            delete item;
        }
    }
};

node* processLine(const char *s) {
    int n = strlen(s);
    char num[109];
    int numSize = 0;
    stack<node*> stck;
    stck.push(new node());
    for (int i = 0; i < n; i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            num[numSize++] = s[i];
        }
        else if (numSize > 0) {
            num[numSize] = 0;
            stck.top()->sons.push_back(new node(atoi(num)));
            numSize = 0;
        }

        if (s[i] == '[') {
            stck.push(new node());
        }
        if (s[i] == ']') {
            node* top = stck.top();
            stck.pop();
            stck.top()->sons.push_back(top);
        }
    }
    return stck.top()->sons[0];
}

string encode(node *a) {
    if (a->isValue) {
        char buf[109];
        snprintf(buf, 109, "%d", a->value);
        return string(buf);
    }
    string ans = "[";
    for (node* item : a->sons) {
        if (ans.size() > 1) {
            ans = ans + ",";
        }
        ans = ans + encode(item);
    }
    ans = ans + "]";
    return ans;
}
    
int compare(node* a, node* b) {
    if (a->isValue && b->isValue) {
        return a->value - b->value;
    }
    if (!a->isValue && !b->isValue) {
        for (int i = 0; i < (int)a->sons.size() && i < (int)b->sons.size(); i++) {
            int cmp = compare(a->sons[i], b->sons[i]);
            if (cmp != 0) {
                return cmp;
            }
        }
        return a->sons.size() - b->sons.size();
    }
    if (!a->isValue) {
        if (a->sons.size() == 0) {
            return -1;
        }
        int cmp = compare(a->sons[0], b);
        if (cmp != 0) {
            return cmp;
        }
        if (a->sons.size() > 1) {
            return 1;
        }
        return 0;
    }
    return -compare(b, a);
}

char tree[MAXN];

int main() {
    vector<node*> trees;
    trees.push_back(processLine("[[2]]"));
    trees.push_back(processLine("[[6]]"));
    while(scanf(" %s", tree) != EOF) {
        trees.push_back(processLine(tree));
    }
    sort(trees.begin(), trees.end(), [](node* a, node* b) {
        return compare(a, b) < 0;
    });
    int ans = 1;
    for (int i = 0; i < (int)trees.size(); i++) {
        string encoded = encode(trees[i]);
        if (encoded == "[[2]]" || encoded == "[[6]]") {
            ans *= i+1;
        }
    }
    printf("%d\n", ans);
    return 0;
}