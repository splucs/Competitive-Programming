#define INF 0x3f3f3f3f

class Solution {
private:
    int n, cnt;
    vector<int> st, en, subXor;
    vector<int> nums;
    vector<vector<int>> g;
    int preorder(int u, int p) {
        subXor[u] = nums[u];
        st[u] = cnt++;
        for (int v : g[u]) {
            if (v == p) {
                continue;
            }
            subXor[u] ^= preorder(v, u);
        }
        en[u] = cnt;
        return subXor[u];
    }
    inline int minArr(int xors[3]) {
        int ans = xors[0];
        for (int i = 1; i < 3; i++) {
            if (ans > xors[i]) {
                ans = xors[i];
            }
        }
        return ans;
    }
    inline int maxArr(int xors[3]) {
        int ans = xors[0];
        for (int i = 1; i < 3; i++) {
            if (ans < xors[i]) {
                ans = xors[i];
            }
        }
        return ans;
    }
public:
    int minimumScore(vector<int>& _nums, vector<vector<int>>& edges) {
        nums.swap(_nums);
        n = nums.size();
        cnt = 0;
        g.resize(n);
        for (vector<int>& e : edges) {
            int u = e[0], v = e[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }

        subXor.resize(n);
        st.resize(n);
        en.resize(n);
        preorder(0, -1);

        int ans = INF;
        int xors[3];
        for (int u = 1; u < n; u++) {
            for (int v = 1; v < u; v++) {
                if (st[v] < st[u] && st[u] < en[v]) { // u is in v's subtree
                    xors[0] = subXor[u];
                    xors[1] = subXor[v] ^ subXor[u];
                    xors[2] = subXor[0] ^ subXor[v];
                } else if (st[u] < st[v] && st[v] < en[u]) { // v is in u's subtree
                    xors[0] = subXor[v];
                    xors[1] = subXor[u] ^ subXor[v];
                    xors[2] = subXor[0] ^ subXor[u];
                } else { // u and v are in distinct subtrees
                    xors[0] = subXor[v];
                    xors[1] = subXor[u];
                    xors[2] = subXor[0] ^ subXor[u] ^ subXor[v];
                }

                ans = min(ans, maxArr(xors) - minArr(xors));
            }
        }
        return ans;
    }
};
