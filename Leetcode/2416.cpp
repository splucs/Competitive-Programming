class Solution {
private:
    vector<vector<int>> go;
    vector<int> score;
    int newNode() {
        go.push_back(vector<int>(26, -1));
        score.push_back(0);
        return go.size()-1;
    }
    void insert(int root, string& word) {
        int u = root;
        for (char c : word) {
            int d = c-'a';
            if (go[u][d] == -1) {
                go[u][d] = newNode();
            }
            u = go[u][d];
            score[u]++;
        }
    }
    int findSum(int root, string& word) {
        int u = root, ans = 0;
        for (char c : word) {
            int d = c-'a';
            u = go[u][d];
            ans += score[u];
        }
        return ans;
    }
public:
    vector<int> sumPrefixScores(vector<string>& words) {
        int root = newNode();
        for (string& word : words) {
            insert(root, word);
        }
        int n = words.size();
        vector<int> ans(n);
        for (int i = 0; i < n; i++) {
            ans[i] = findSum(root, words[i]);
        }
        return ans;
    }
};
