class Solution {
private:
    vector<vector<int>> go;
    int newNode() {
        go.push_back(vector<int>(10, -1));
        return go.size()-1;
    }
    void insert(vector<int> x) {
        int u = 0;
        for (int d : x) {
            if (go[u][d] == -1) {
                go[u][d] = newNode();
            }
            u = go[u][d];
        }
    }
    int find(vector<int> y) {
        int ans = 0, u = 0;
        for (int d : y) {
            if (go[u][d] == -1) {
                return ans;
            }
            ans++;
            u = go[u][d];
        }
        return ans;
    }
    vector<int> digits(int x) {
        vector<int> ans;
        while (x) {
            ans.push_back(x%10);
            x /= 10;
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
public:
    int longestCommonPrefix(vector<int>& arr1, vector<int>& arr2) {
        newNode();
        for (int x : arr1) {
            insert(digits(x));
        }
        int ans = 0;
        for (int y : arr2) {
            ans = max(ans, find(digits(y)));
        }
        return ans;
    }
};
