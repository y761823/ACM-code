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
    ListNode *res = nullptr, *ir = nullptr;

    void addNum(int &num) {
        if (!ir)
            res = ir = new ListNode(num % 10);
        else
            ir->next = new ListNode(num % 10),
            ir = ir->next;
        num /= 10;
    }

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *i1 = l1, *i2 = l2;
        int sum = 0;
        while (i1 != nullptr || i2 != nullptr)
        {
            if (i1) sum += i1->val, i1 = i1->next;
            if (i2) sum += i2->val, i2 = i2->next;
            addNum(sum);
        }
        if (sum) addNum(sum);
        return res;
    }
};
