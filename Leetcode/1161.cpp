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
    int maxLevelSum(TreeNode* root) {
        vector<int> depth(2, 0);
        calcLevels(root, 1, depth);
        int ans = 0, maxSum = -1e9;
        for (int h = 1; h < (int)depth.size(); h++) {
            if (depth[h] > maxSum) {
                maxSum = depth[h];
                ans = h;
            }
        }
        return ans;
    }
    void calcLevels(TreeNode *u, int h, vector<int> &depth) {
        if (h >= depth.size()) depth.push_back(0);
        depth[h] += u->val;
        if (u->left) calcLevels(u->left, h+1, depth);
        if (u->right) calcLevels(u->right, h+1, depth);
    }
};
