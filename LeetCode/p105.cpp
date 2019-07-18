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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        function<TreeNode*(int, int, int)> dfs = [&](int a, int b, int len) -> TreeNode* {
            if (len == 0)
                return nullptr;
            TreeNode* p = new TreeNode(preorder[a]);
            int bp = find(inorder.begin() + b, inorder.end(), p->val) - inorder.begin();
            int lSize = bp - b;
            p->left = dfs(a + 1, b, lSize);
            p->right = dfs(a + 1 + lSize, bp + 1, len - lSize - 1);
            return p;
        };
        return dfs(0, 0, preorder.size());
    }
};
