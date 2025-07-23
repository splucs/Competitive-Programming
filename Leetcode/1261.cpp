/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class FindElements {
private:
    TreeNode* root;
    void recover(TreeNode* u, int val) {
        u->val = val;
        if (u->left != NULL) {
            recover(u->left, 2*val+1);
        }
        if (u->right != NULL) {
            recover(u->right, 2*val+2);
        }
    }
public:
    FindElements(TreeNode* _root) {
        root = _root;
        recover(root, 0);
    }
    
    bool find(int target) {
        vector<int> path;
        for(int x = target; x > 0; x = (x-1)/2) {
            path.push_back(x);
        }
        reverse(path.begin(), path.end());

        TreeNode* u = root;
        for (int x : path) {
            if (u->left != NULL && u->left->val == x) {
                u = u->left;
            } else if (u->right != NULL && u->right->val == x) {
                u = u->right;
            } else {
                return false;
            }
        }
        return true;
    }
};

/**
 * Your FindElements object will be instantiated and called as such:
 * FindElements* obj = new FindElements(root);
 * bool param_1 = obj->find(target);
 */
