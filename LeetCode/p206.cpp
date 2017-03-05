/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode *newh = nullptr, *cur = head;
        while (cur) {
            ListNode* t = cur->next;
            cur->next = newh;
            newh = cur;
            cur = t;
        }
        return newh;
    }
};
