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
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        TreeNode* p = root;
        while (p) {
            if (!p->left) {
                res.push_back(p->val);
                p = p->right;
            } else {
                TreeNode* q = p->left;
                while (q->right && q->right != p)
                    q = q->right;
                if (!q->right) {
                    res.push_back(p->val);
                    q->right = p;
                    p = p->left;
                } else {
                    q->right = nullptr;
                    p = p->right;
                }
            }
        }
        return res;
    }
};
