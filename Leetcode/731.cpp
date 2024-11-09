#define MAXN 999999999
class MyCalendarTwo {
private:
    int root;
    vector<int> left, right, calendar, lazy;
    int newNode() {
        left.push_back(-1);
        right.push_back(-1);
        calendar.push_back(0);
        lazy.push_back(0);
        return calendar.size()-1;
    }
    void push(int u, int l, int r) {
        if (l < r) {
            if (left[u] == -1) {
                left[u] = newNode();
            }
            lazy[left[u]] += lazy[u];
            if (right[u] == -1) {
                right[u] = newNode();
            }
            lazy[right[u]] += lazy[u];
        }
        calendar[u] += lazy[u];
        lazy[u] = 0;
    }
    bool check(int u, int l, int r, int start, int end) {
        push(u, l, r);
        if (r < start || end < l) {
            return true;
        }
        if (start <= l && r <= end) {
            return calendar[u] < 2;
        }
        int mid = (l + r)>>1;
        return check(left[u], l, mid, start, end)
            && check(right[u], mid+1, r, start, end);
    }
    void doBook(int u, int l, int r, int start, int end) {
        push(u, l, r);
        if (r < start || end < l) {
            return;
        }
        if (start <= l && r <= end) {
            lazy[u]++;
            push(u, l, r);
            return;
        }
        int mid = (l + r)>>1;
        doBook(left[u], l, mid, start, end);
        doBook(right[u], mid+1, r, start, end);
        calendar[u] = max(calendar[left[u]], calendar[right[u]]);
    }
public:
    MyCalendarTwo() {
        root = newNode();
    }
    
    bool book(int start, int end) {
        if (!check(root, 0, MAXN, start, end-1)) {
            return false;
        }
        doBook(root, 0, MAXN, start, end-1);
        return true;
    }
};

/**
 * Your MyCalendarTwo object will be instantiated and called as such:
 * MyCalendarTwo* obj = new MyCalendarTwo();
 * bool param_1 = obj->book(start,end);
 */
