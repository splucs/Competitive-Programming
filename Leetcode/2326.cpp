/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> spiralMatrix(int m, int n, ListNode* head) {
        vector<vector<int>> ans(m, vector<int>(n, -1));
        int i = 0, j = 0, di = 0, dj = 1;
        for (ListNode* u = head; u != NULL; u = u->next) {
            ans[i][j] = u->val;
            int ni = i + di;
            int nj = j + dj;
            if (ni < 0 || nj < 0 || ni >= m || nj >= n || ans[ni][nj] != -1) {
                di = -di;
                swap(di, dj);
                ni = i + di;
                nj = j + dj;
            }
            i = ni;
            j = nj;
        }
        return ans;
    }
};
