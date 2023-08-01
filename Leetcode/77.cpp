class Solution {
private:
    vector<int> cur;
    vector<vector<int>> ans;
    void recurse(int i, int n, int k) {
        if (k == 0) {
            ans.push_back(cur);
            return;
        }
        if (n-i+1 < k) return;
        cur.push_back(i);
        recurse(i+1, n, k-1);
        cur.pop_back();
        recurse(i+1, n, k);
    }
public:
    vector<vector<int>> combine(int n, int k) {
        cur.clear();
        ans.clear();
        recurse(1, n, k);
        return ans;
    }
};
