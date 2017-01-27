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
    ListNode* swapPairs(ListNode* head) {
        if (!head) return head;
        
        ListNode myhead(0), *p = &myhead;
        myhead.next = head;
        
        while (p->next && p->next->next) {
            ListNode* q = p->next;
            p->next = q->next;
            q->next = q->next->next;
            p->next->next = q;
            p = q;
        }
        
        return myhead.next;
    }
};
