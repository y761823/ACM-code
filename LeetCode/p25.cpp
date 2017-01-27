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
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode myHead(0), *p = &myHead;
        p->next = head;
        
        while (p->next) {
            ListNode *test = p;
            for (int i = 0; i < k; ++i)
                if (!(test = test->next)) return myHead.next;
            
            ListNode *old = p->next;
            for (int i = 1; i < k; ++i) {
                ListNode *now = old->next;
                old->next = now->next;
                now->next = p->next;
                p->next = now;
            }
            p = old;
        }
        
        return myHead.next;
    }
};
