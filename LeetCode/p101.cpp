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
    bool isMirror(TreeNode* a, TreeNode* b) {
        if (a && b) {
            return a->val == b->val &&
                isMirror(a->left, b->right) &&
                isMirror(a->right, b->left);
        } else {
            return !a && !b;
        }
    }

    bool isSymmetric(TreeNode* root) {
        return !root || isMirror(root->left, root->right);
    }
};
