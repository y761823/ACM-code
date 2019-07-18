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
    void reorderList(ListNode* head) {
        if (!head)
            return ;
        
        ListNode *slow = head, *fast = head->next;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode* right = reverse(slow->next);
        slow->next = nullptr;
        
        while (right) {
            ListNode* nextr = right->next;
            right->next = head->next;
            head->next = right;
            head = right->next;
            right = nextr;
        }
    }
    
    ListNode* reverse(ListNode* p) {
        ListNode* pre = nullptr;
        while (p) {
            ListNode* t = p->next;
            p->next = pre;
            pre = p;
            p = t;
        }
        return pre;
    }
};
