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
    int res = numeric_limits<int>::min();

    int maxSum(TreeNode* root) {
        if (!root) return 0;
        int left = maxSum(root->left);
        int right = maxSum(root->right);
        res = max(res, root->val + left + right);
        return max(root->val + max(left, right), 0);
    }

    int maxPathSum(TreeNode* root) {
        maxSum(root);
        return res;
    }
};
