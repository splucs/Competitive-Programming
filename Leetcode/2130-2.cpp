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
    int pairSum(ListNode* head) {
        int ans = 0;
        int n = 0;
        for (ListNode* u = head; u; u = u->next) n++;
        solve(head, n, ans);
        return ans;
    }
    ListNode* solve(ListNode* head, int n, int &ans) {
        if (n == 0) {
            return head;
        }
        ListNode *last = solve(head->next, n-2, ans);
        if (ans < head->val + last->val) {
            ans = head->val + last->val;
        }
        return last->next;
    }
};
