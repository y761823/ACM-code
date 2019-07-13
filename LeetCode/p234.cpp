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
    bool isPalindrome(ListNode* head) {
        if (!head)
            return true;
        ListNode *fast = head->next, *slow = head;
        while (fast && fast->next) {
            fast = fast->next->next;
            slow = slow->next;
        }
        
        ListNode* p = reverse(slow->next);
        while (p && p->val == head->val) {
            p = p->next;
            head = head->next;
        }
        return !p;
    }
    
    ListNode* reverse(ListNode* head) {
        ListNode* pre = nullptr;
        while (head) {
            ListNode* p = head->next;
            head->next = pre;
            pre = head;
            head = p;
        }
        return pre;
    }
};
