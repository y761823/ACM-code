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
    bool isValidBST(TreeNode* root) {
        int lastVal = 0;
        TreeNode* cur = root;
        bool res = true, firstNode = true;
        while (cur) {
            if (!cur->left) {
                if (!firstNode && lastVal >= cur->val)
                    res = false;
                firstNode = false;
                lastVal = cur->val;
                cur = cur->right;
            } else {
                TreeNode* pre = cur->left;
                while (pre->right && pre->right != cur)
                    pre = pre->right;
                if (!pre->right) {
                    pre->right = cur;
                    cur = cur->left;
                } else {
                    if (!firstNode && lastVal >= cur->val)
                        res = false;
                    firstNode = false;
                    lastVal = cur->val;
                    pre->right = nullptr;
                    cur = cur->right;
                }
            }
        }
        return res;
    }
};
