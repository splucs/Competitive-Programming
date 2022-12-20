#include <bits/stdc++.h>
using namespace std;
#define MAXN 4000009

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

void markFull(node *n) {
    n->full = true;
    if (n->left) {
        delete n->left;
        n->left = NULL;
    }
    if (n->right) {
        delete n->right;
        n->right = NULL;
    }
}

void insert(node *n, int l, int r) {
    if (n->full) {
        return;
    }
    if (n->r < l || r < n->l) {
        return;
    }
    else if (l <= n->l && n->r <= r) {
        markFull(n);
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
    if (n->left->full && n->right->full) {
        markFull(n);
    }
}

int ans;

bool query(node *n, int l, int r) {
    if (n->full) {
        return false;
    }
    if (n->left || n->right) {
        return query(n->left, l, r) || query(n->right, l, r);
    }
    else {
        ans = n->l;
        if (n->r > n->l) {
            printf("something wrong happened\n");
            exit(1);
        }
        return true;
    }
}

node* roots[MAXN];

int abs(int x) {
    return x < 0 ? -x : x;
}

int main() {
    const int minx = 0;
    const int miny = 0;
    const int maxx = 4000000;
    const int maxy = 4000000;

    for (int i = 0; i < MAXN; i++) {
        roots[i] = new node(minx, maxx);
    }

    int sx, sy, bx, by;
    while(scanf(" Sensor at x=%d, y=%d: closest beacon is at x=%d, y=%d", &sx, &sy, &bx, &by) != EOF) {
        int d = abs(sx-bx) + abs(sy-by);
        for (int y = max(sy-d, miny); y <= min(sy+d, maxy); y++) {
            int dy = abs(y - sy);
            int dx = d - dy;
            insert(roots[y], max(sx-dx, minx), min(sx+dx, maxx));
        }
    }
    for (int y = miny; y <= maxy; y++) {
        if (query(roots[y], minx, maxx)) {
            printf("%lld\n", ans*4000000LL + y);
        }
    }
    return 0;
}