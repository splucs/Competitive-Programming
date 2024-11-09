class Solution {
private:
    vector<int> ans;
    void iterate(int limit, int cur) {
        ans.push_back(cur);
        cur *= 10;
        for (int i = 0; i < 10 && cur+i <= limit; i++) {
            iterate(limit, cur+i);
        }
    }
public:
    vector<int> lexicalOrder(int n) {
        for (int i = 1; i < 10 && i <= n; i++) {
            iterate(n, i);
        }
        return ans;
    }
};
