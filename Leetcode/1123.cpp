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
    TreeNode* dfs(TreeNode* u, int& depth) {
        if (u == NULL) {
            return NULL;
        }
        int depthL = 0, depthR = 0;
        TreeNode* ansL = dfs(u->left, depthL);
        TreeNode* ansR = dfs(u->right, depthR);
        depth = 1 + max(depthL, depthR);
        if (depthR > depthL) return ansR;
        if (depthR < depthL) return ansL;
        return u;
    }
public:
    TreeNode* lcaDeepestLeaves(TreeNode* root) {
        int treeDepth;
        return dfs(root, treeDepth);
    }
};
