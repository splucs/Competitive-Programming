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
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        int i = 1;
        ListNode *prev = NULL, *nxt = NULL;
        ListNode *first = NULL, *last = NULL;
        ListNode *before = NULL, *after = NULL;
        for (ListNode *u = head; u != NULL; prev = u, u = nxt, i++) {
            nxt = u->next;
            if (i == left) {
                first = u;
                before = prev;
            }
            if (i == right) {
                last = u;
                after = nxt;
            }
            if (i > left && i <= right) {
                u->next = prev;
            }
        }
        first->next = after;
        if (before != NULL) before->next = last;
        if (left == 1) {
            return last;
        }
        return head;
    }
};
