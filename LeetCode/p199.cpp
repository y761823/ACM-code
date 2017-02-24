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
    vector<int> res;
    
    void dfs(TreeNode* p, int dep = 0) {
        if (!p) return ;
        if (dep == res.size()) res.push_back(p->val);
        dfs(p->right, dep + 1);
        dfs(p->left, dep + 1);
    }

    vector<int> rightSideView(TreeNode* root) {
        dfs(root);
        return res;
    }
};
