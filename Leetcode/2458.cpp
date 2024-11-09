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
    vector<int> maxDepth, depth, ansForNode;

    int calculateMaxDepth(TreeNode* u, int d) {
        while (maxDepth.size() <= u->val) {
            maxDepth.push_back(0);
            depth.push_back(0);
            ansForNode.push_back(0);
        }
        int maxD = d; 
        depth[u->val] = d;
        
        if (u->left != NULL) {
            maxD = max(maxD, calculateMaxDepth(u->left, d+1));
        }
        if (u->right != NULL) {
            maxD = max(maxD, calculateMaxDepth(u->right, d+1));
        }
        return maxDepth[u->val] = maxD;
    }
    
    void solve(TreeNode* u, int upstreamMaxDepth) {
        ansForNode[u->val] = upstreamMaxDepth;
    
        if (u->left != NULL) {
            solve(u->left, max(upstreamMaxDepth, u->right != NULL ? maxDepth[u->right->val] : depth[u->val]));
        }
        if (u->right != NULL) {
            solve(u->right, max(upstreamMaxDepth, u->left != NULL ? maxDepth[u->left->val] : depth[u->val]));
        }
    }
public:
    vector<int> treeQueries(TreeNode* root, vector<int>& queries) {
        calculateMaxDepth(root, 0);
        solve(root, 0);
        vector<int> ans(queries.size());
        for (int q = 0; q < (int)queries.size(); q++) {
            ans[q] = ansForNode[queries[q]];
        }
        return ans;
    }
};
