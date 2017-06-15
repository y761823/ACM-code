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
    ListNode* oddEvenList(ListNode* head) {
        ListNode h1(0), h2(0);
        ListNode *p1 = &h1, *p2 = &h2;
        bool odd = false;
        for (ListNode* p = head; p; p = p->next) {
            odd = !odd;
            if (odd) p1->next = p, p1 = p;
            else p2->next = p, p2 = p;
        }
        p1->next = h2.next; p2->next = nullptr;
        return h1.next;
    }
};
