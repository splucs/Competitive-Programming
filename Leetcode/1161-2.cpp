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
    vector<int> depth;
public:
    int maxLevelSum(TreeNode* root) {
        depth.assign(2, 0);
        calcLevels(root, 1);
        int ans = 0, maxSum = -1e9;
        for (int h = 1; h < (int)depth.size(); h++) {
            if (depth[h] > maxSum) {
                maxSum = depth[h];
                ans = h;
            }
        }
        return ans;
    }
    void calcLevels(TreeNode *u, int h) {
        if (h >= depth.size()) depth.push_back(0);
        depth[h] += u->val;
        if (u->left) calcLevels(u->left, h+1);
        if (u->right) calcLevels(u->right, h+1);
    }
};
