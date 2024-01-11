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
    int dfs(TreeNode* u, int &minVal, int &maxVal) {
        minVal = maxVal = u->val;
        int ans = 0;

        int ansLeft = 0;
        if (u->left != NULL) {
            int minLeft = 1e5, maxLeft = 0;
            ansLeft = dfs(u->left, minLeft, maxLeft);
            minVal = min(minVal, minLeft);
            maxVal = max(maxVal, maxLeft);
        }

        int ansRight = 0;
        if (u->right != NULL) {
            int minRight = 1e5, maxRight = 0;
            ansRight = max(ans, dfs(u->right, minRight, maxRight));
            minVal = min(minVal, minRight);
            maxVal = max(maxVal, maxRight);
        }

        return max(
            max(ansLeft, ansRight),
            max(u->val - minVal, maxVal - u->val));
    }
public:
    int maxAncestorDiff(TreeNode* root) {
        int minVal = 1e5, maxVal = 0;
        return dfs(root, minVal, maxVal);
    }
};
