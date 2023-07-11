/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
private:
    vector<TreeNode*> pathToTarget;
    vector<int> ans;
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        pathToTarget.clear();
        ans.clear();

        findPathToTarget(root, target);

        int n = pathToTarget.size();
        for (int i = n-1; i >= 0 && i >= n-k; i--) {
            TreeNode *u = pathToTarget[i];
            TreeNode *nxt = i+1 < n ? pathToTarget[i+1] : NULL;
            if (u->left != nxt) {
                appendNodesAtDepth(u->left, k+i-n);
            }
            if (u->right != nxt) {
                appendNodesAtDepth(u->right, k+i-n);
            }
        }
        if (k < n) {
            ans.push_back(pathToTarget[n-1-k]->val);
        }
        return ans;
    }
    bool findPathToTarget(TreeNode *u, TreeNode* target) {
        if (!u) return false;
        pathToTarget.push_back(u);
        if (u->val == target->val) return true;
        if (findPathToTarget(u->left, target)) return true;
        if (findPathToTarget(u->right, target)) return true;
        pathToTarget.pop_back();
        return false;
    }
    void appendNodesAtDepth(TreeNode *u, int k) {
        if (k < 0 || !u) return;
        if (k == 0) {
            ans.push_back(u->val);
            return;
        }
        appendNodesAtDepth(u->left, k-1);
        appendNodesAtDepth(u->right, k-1);
    }
};
