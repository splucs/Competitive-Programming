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
    string path;
    string startPath, destPath;
    int startValue, destValue;
    
    void search(TreeNode *u) {
        if (u->val == startValue) {
            startPath = path;
        }
        if (u->val == destValue) {
            destPath = path;
        }
        if (u->left != NULL) {
            path.push_back('L');
            search(u->left);
            path.pop_back();
        }
        if (u->right != NULL) {
            path.push_back('R');
            search(u->right);
            path.pop_back();
        }
    }
public:
    string getDirections(TreeNode* root, int _startValue, int _destValue) {
        startValue = _startValue;
        destValue = _destValue;
        search(root);

        int pref = 0;
        for (; pref < (int)startPath.size() && pref < (int)destPath.size(); pref++) {
            if (startPath[pref] != destPath[pref]) {
                break;
            }
        }

        string ans;
        for (int i = pref; i < (int)startPath.size(); i++) {
            ans.push_back('U');
        }
        for (int i = pref; i < (int)destPath.size(); i++) {
            ans.push_back(destPath[i]);
        }
        return ans;
    }
};
