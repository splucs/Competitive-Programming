class Solution {
private:
    void dfs(Node* u, Node* v) {
        if (u == NULL) {
            return;
        }
        u->next = v;
        dfs(u->left, u->right);
        dfs(u->right, v == NULL ? NULL : v->left);
    }
public:
    Node* connect(Node* root) {
        dfs(root, NULL);
        return root;
    }
};
