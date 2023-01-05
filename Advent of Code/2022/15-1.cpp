#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000009

struct node {
    int l, r;
    node *left;
    node *right;
    bool full;
    node(int _l, int _r) : l(_l), r(_r), left(NULL), right(NULL), full(false) {}
    ~node() {
        if (left) delete left;
        if (right) delete right;
    }
};

void insert(node *n, int l, int r) {
    if (n->full) {
        return;
    }
    if (n->r < l || r < n->l) {
        return;
    }
    else if (l <= n->l && n->r <= r) {
        n->full = true;
        if (n->left) {
            delete n->left;
            n->left = NULL;
        }
        if (n->right) {
            delete n->right;
            n->right = NULL;
        }
        return;
    }
    int mid = (n->l+n->r)/2;
    if (!n->left) {
        n->left = new node(n->l, mid);
    }
    if (!n->right) {
        n->right = new node(mid+1, n->r);
    }
    insert(n->left, l, r);
    insert(n->right, l, r);
}

int compute(node *n) {
    if (!n) {
        return 0;
    }
    if (n->full) {
        return n->r - n->l + 1;
    }
    return compute(n->left) + compute(n->right);
}

int abs(int x) {
    return x < 0 ? -x : x;
}

int main() {
    const int rowOfInterest = 2000000;
    int sx, sy, bx, by;
    node *root = new node(-100000000, 100000000);
    set<int> beaconsAtRowOfInterest;
    while(scanf(" Sensor at x=%d, y=%d: closest beacon is at x=%d, y=%d", &sx, &sy, &bx, &by) != EOF) {
        int d = abs(sx-bx) + abs(sy-by);
        int dy = abs(rowOfInterest - sy);
        int dx = d - dy;
        if (dx < 0) {
            continue;
        }
        insert(root, sx-dx, sx+dx);
        if (by == rowOfInterest) {
            beaconsAtRowOfInterest.insert(bx);
        }
    }
    printf("%d\n", compute(root) - (int)beaconsAtRowOfInterest.size());
    return 0;
}