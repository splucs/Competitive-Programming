#define left(u) (u<<1)
#define right(u) ((u<<1)+1)

class Solution {
private:
    vector<int> st, baskets;

    void build(int u, int l, int r) {
        if (l == r) {
            st[u] = baskets[l];
            return;
        }
        int mid = (l+r) >> 1;
        build(left(u), l, mid);
        build(right(u), mid+1, r);
        st[u] = max(st[left(u)], st[right(u)]);
    }
    bool query(int u, int l, int r, int fruit) {
        if (st[u] < fruit) {
            return false;
        }
        if (l == r) {
            st[u] = 0;
            return true;
        }
        int mid = (l+r) >> 1;
        bool ans = query(left(u), l, mid, fruit) || query(right(u), mid+1, r, fruit);
        st[u] = max(st[left(u)], st[right(u)]);
        return ans;
    }
public:
    int numOfUnplacedFruits(vector<int>& fruits, vector<int>& _baskets) {
        baskets.swap(_baskets);
        st.resize(4*baskets.size());
        int n = baskets.size(), root = 1;

        build(root, 0, n-1);
        int ans = 0;
        for (int fruit : fruits) {
            if (!query(root, 0, n-1, fruit)) {
                ans++;
            }
        }
        return ans;
    }
};
