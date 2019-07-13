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
    void deleteNode(ListNode* node) {
        ListNode* pre = nullptr;
        while (node->next) {
            node->val = node->next->val;
            pre = node;
            node = node->next;
        }
        delete node;
        pre->next = nullptr;
    }
};
