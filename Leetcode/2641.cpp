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
    vector<int> depthSum;
    void calculateDepthSum(TreeNode* u, int d) {
        if (depthSum.size() == d) {
            depthSum.push_back(0);
        }
        depthSum[d] += u->val;
        if (u->left != NULL) {
            calculateDepthSum(u->left, d+1);
        }
        if (u->right != NULL) {
            calculateDepthSum(u->right, d+1);
        }
    }
    void convert(TreeNode* u, int siblingVal, int d) {
        u->val = depthSum[d] - u->val - siblingVal;
        int leftVal = u->left == NULL ? 0 : u->left->val;
        int rightVal = u->right == NULL ? 0 : u->right->val;
        if (u->left != NULL) {
            convert(u->left, rightVal, d+1);
        }
        if (u->right != NULL) {
            convert(u->right, leftVal, d+1);
        }
    }
public:
    TreeNode* replaceValueInTree(TreeNode* root) {
        calculateDepthSum(root, 0);
        convert(root, 0, 0);
        return root;
    }
};
