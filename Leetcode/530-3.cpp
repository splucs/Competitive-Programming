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
public:
    int getMinimumDifference(TreeNode* root) {
        int last = -1;
        return recurse(root, last);
    }
    int recurse(TreeNode *u, int &last) {
        int ans = 1e7;

        if (u->left) {
            int curAns = recurse(u->left, last);
            ans = ans > curAns ? curAns : ans;
        }

        if (last >= 0) {
            int curAns = u->val - last;
            ans = ans > curAns ? curAns : ans;
        }
        last = u->val;

        if (u->right) {
            int curAns = recurse(u->right, last);
            ans = ans > curAns ? curAns : ans;
        }

        return ans;
    }
};
