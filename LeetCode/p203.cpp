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
    ListNode* removeElements(ListNode* head, int val) {
        ListNode myHead(0); myHead.next = head;
        ListNode* p = &myHead;
        while (p->next) {
            if (p->next->val == val)
                p->next = p->next->next;
            else
                p = p->next;
        }
        return myHead.next;
    }
};
