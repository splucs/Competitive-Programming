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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int balance = size(l1) - size(l2);
        if (balance < 0) {
            balance = -balance;
            swap(l1, l2);
        }

        int carry = 0;
        ListNode* ans = add(l1, l2, carry, balance);
        if (carry > 0) {
            ans = new ListNode(carry, ans);
        }
        return ans;
    }
    ListNode* add(ListNode* l1, ListNode* l2, int& carry, int balance) {
        ListNode* tail;
        int sum;
        if (balance > 0) {
            tail = add(l1->next, l2, carry, balance-1);
            sum = l1->val + carry;
        } else {
            if (l1->next == NULL && l2->next == NULL) {
                tail = NULL;
                carry = 0;
            } else {
                tail = add(l1->next, l2->next, carry, 0);
            }
            sum = l1->val + l2->val + carry;
        }
        ListNode* head = new ListNode(sum%10, tail);
        carry = sum/10;
        return head;
    }
    int size(ListNode* l) {
        int ans = 0;
        for (; l; l = l->next) {
            ans++;
        }
        return ans;
    }
};
