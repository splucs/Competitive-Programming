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
private:
    ListNode* addWithCarry(ListNode* l1, ListNode* l2, int carry) {
        if (carry == 0 && l1 == NULL && l2 == NULL) {
            return NULL;
        }

        int sum = carry + (l1 != NULL ? l1->val : 0) + (l2 != NULL ? l2->val : 0);

        if (sum >= 10) {
            sum -= 10;
            carry = 1;
        } else {
            carry = 0;
        }
        return new ListNode(sum, addWithCarry(l1 != NULL ? l1->next : NULL, l2 != NULL ? l2->next : NULL, carry));
    }
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* ans = addWithCarry(l1, l2, 0);
        return ans != NULL ? ans : new ListNode(0);
    }
};
