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
    int curCount;
    int cur;
    int ansCount;
    vector<int> ans;
        
    void process(int x) {
        if (x != cur) {
            if (curCount > ansCount) {
                ans.clear();
                ansCount = curCount;
            }
            if (curCount == ansCount) ans.push_back(cur);
            curCount = 0;
            cur = x;
        }
        curCount++;
    }

    void inorder(TreeNode* root) {
        if (!root) return;
        inorder(root->left);
        process(root->val);
        inorder(root->right);
    }
public:
    vector<int> findMode(TreeNode* root) {
        curCount = cur = ansCount = 0;
        ans.clear();
        inorder(root);
        process(-1);
        return ans;
    }
};
