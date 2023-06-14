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
        int minRoot, maxRoot;
        return calcMinMax(root, minRoot, maxRoot);
    }
    int calcMinMax(TreeNode *u, int &minu, int &maxu) {
        int ans = 1e7;
        minu = maxu = u->val;
        if (u->left) {
            int minl, maxl;
            int curAns = calcMinMax(u->left, minl, maxl);
            int diff = u->val - maxl;
            curAns = curAns > diff ? diff : curAns;
            ans = curAns > ans ? ans : curAns;
            minu = minl;
        }
        if (u->right) {
            int minr, maxr;
            int curAns = calcMinMax(u->right, minr, maxr);
            int diff = minr - u->val;
            curAns = curAns > diff ? diff : curAns;
            ans = curAns > ans ? ans : curAns;
            maxu = maxr;
        }
        return ans;
    }
};
