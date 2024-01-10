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
    int ans;
    int search(TreeNode* u, int start) {
        if (u == NULL) {
            return -1;
        }

        if (u->val == start) {
            infect(u, 0);
            return 0;
        }

        int dist = search(u->left, start);
        if (dist != -1) {
            ans = max(ans, dist+1);
            infect(u->right, dist+2);
            return dist+1;
        }
        dist = search(u->right, start);
        if (dist != -1) {
            ans = max(ans, dist+1);
            infect(u->left, dist+2);
            return dist+1;
        }
        return -1;
    }
    void infect(TreeNode* u, int dist) {
        if (u == NULL) {
            return;
        }
        ans = max(ans, dist);
        infect(u->left, dist+1);
        infect(u->right, dist+1);
    }
public:
    int amountOfTime(TreeNode* root, int start) {
        ans = 0;
        search(root, start);
        return ans;
    }
};
