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
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        ListNode tempHead(0);
        tempHead.next = head;
        ListNode* pm = &tempHead;
        for (int i = 1; i < m; ++i)
            pm = pm->next;
        ListNode* revLast = pm->next;
        
        ListNode* p = revLast->next;
        for (int i = m; i < n; ++i) {
            ListNode* temp = p->next;
            p->next = pm->next;
            pm->next = p;
            p = temp;
        }
        revLast->next = p;
        return tempHead.next;
    }
};
