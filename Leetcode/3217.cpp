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
    ListNode* modifiedList(vector<int>& nums, ListNode* head) {
        unordered_set<int> numSet(nums.begin(), nums.end());
        ListNode ans;
        for (ListNode *u = head, *prev = &ans; u != NULL; u = u->next) {
            if (numSet.count(u->val)) {
                continue;
            }
            prev = prev->next = new ListNode(u->val);
        }
        return ans.next;
    }
};
