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
        vector<TreeNode*> nodes;
        // op: 'o' = open node, 'e' = evaluate node
        vector<char> ops;

        nodes.push_back(root); ops.push_back('o');

        int last = -1;
        int ans = 1e7;
        while(!nodes.empty()) {
            TreeNode *u = nodes.back(); nodes.pop_back();
            char op = ops.back(); ops.pop_back();
            if (!u) continue;

            if (op == 'o') {
                nodes.push_back(u->right); ops.push_back('o');
                nodes.push_back(u); ops.push_back('e');
                nodes.push_back(u->left); ops.push_back('o');
            } else if (op == 'e') {
                if (last >= 0) {
                    int curAns = u->val - last;
                    ans = curAns > ans ? ans : curAns;
                }
                last = u->val;
            }
        }
        return ans;
    }
};
