class Solution {
private:
    string ans;
    void preorder(TreeNode* u) {
        if (u == NULL) {
            return;
        }
        ans += to_string(u->val);
        if (u->left != NULL || u->right != NULL) {
            ans += "(";
            preorder(u->left);
            ans += ")";
        }
        if (u->right != NULL) {
            ans += "(";
            preorder(u->right);
            ans += ")";
        }
    }
public:
    string tree2str(TreeNode* root) {
        ans.clear();
        preorder(root);
        return ans;
    }
};
