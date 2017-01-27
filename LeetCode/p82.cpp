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
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode myhead(0), *p = &myhead;
        myhead.next = head;
        
        while (p->next) {
            ListNode *q = p->next;
            if (q->next && q->val == q->next->val) {
                int val = q->val;
                while (p->next && p->next->val == val) {
                    q = p->next;
                    p->next = p->next->next;
                    delete q;
                }
            } else {
                p = p->next;
            }
        }
        return myhead.next;
    }
};
