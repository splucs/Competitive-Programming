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
    unordered_map<int, TreeNode*> nodes;
    int root;
    TreeNode* getNode(int x) {
        root = x;
        if (!nodes.count(x)) {
            nodes[x] = new TreeNode(x);
        }
        return nodes[x];
    }
public:
    TreeNode* createBinaryTree(vector<vector<int>>& descriptions) {
        unordered_map<int, int> parents;
        for (int i = 0; i < (int)descriptions.size(); i++) {
            TreeNode* u = getNode(descriptions[i][0]);
            TreeNode* v = getNode(descriptions[i][1]);
            int isLeft = descriptions[i][2];
            if (isLeft == 1) {
                u->left = v;
            } else {
                u->right = v;
            }
            parents[v->val] = u->val;
        }
        while (parents.count(root)) {
            root = parents[root];
        }
        return nodes[root];
    }
};
