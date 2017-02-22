/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    void reverse(TreeNode* from, TreeNode* to) {
        TreeNode *a = from, *b = from->right, *c;
        a->right = nullptr;
        while (b) {
            c = b->right;
            b->right = a;
            a = b;
            b = c;
        }
    }
    
    void printReverse(vector<int> &res, TreeNode* from, TreeNode* to) {
        reverse(from, to);
        for (TreeNode* p = to; p != from; p = p->right)
            res.push_back(p->val);
        res.push_back(from->val);
        reverse(from, to);
    }

    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        TreeNode super(0);
        super.left = root;
        TreeNode *cur = &super;
        while (cur) {
            if (!cur->left) {
                cur = cur->right;
            } else {
                TreeNode *pre = cur->left;
                while (pre->right && pre->right != cur)
                    pre = pre->right;
                if (!pre->right) {
                    pre->right = cur;
                    cur = cur->left;
                } else {
                    pre->right = nullptr;
                    printReverse(res, cur->left, pre);
                    cur = cur->right;
                }
            }
        }
        return res;
    }
};
