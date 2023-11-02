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
    int ans;
    pair<int, int> process(TreeNode* node) {
        int sum = node->val;
        int cnt = 1;
        if (node->left) {
            pair<int, int> child = process(node->left);
            sum += child.first;
            cnt += child.second;
        }
        if (node->right) {
            pair<int, int> child = process(node->right);
            sum += child.first;
            cnt += child.second;
        }
        if (sum/cnt == node->val) {
            ans++;
        }
        return make_pair(sum, cnt);
    }
public:
    int averageOfSubtree(TreeNode* root) {
        ans = 0;
        process(root);
        return ans;
    }
};
