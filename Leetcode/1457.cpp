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
class Solution {
private:
    int oddMask;
    int numOdd;
    int recurse(TreeNode* u) {
        flip(u->val);
        
        int ans = 0;
        if (u->left == NULL && u->right == NULL) {
            ans = numOdd <= 1 ? 1 : 0;
        } else {
            if (u->left != NULL) {
                ans += recurse(u->left);
            }
            if (u->right != NULL) {
                ans += recurse(u->right);
            }
        }

        flip(u->val);
        return ans;
    }
    void flip(int v) {
        oddMask ^= (1<<v);
        if (oddMask&(1<<v)) numOdd++;
        else numOdd--;
    }
public:
    int pseudoPalindromicPaths (TreeNode* root) {
        oddMask = 0;
        numOdd = 0;
        return recurse(root);
    }
};
