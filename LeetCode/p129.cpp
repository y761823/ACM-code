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
    int res = 0;
    void dfs(TreeNode* p, string &cur) {
        cur.push_back(p->val + '0');
        if (!p->left && !p->right) {
            res += stoi(cur);
        } else {
            if (p->left) dfs(p->left, cur);
            if (p->right) dfs(p->right, cur);
        }
        cur.pop_back();
    }
public:
    int sumNumbers(TreeNode* root) {
        string tmp;
        if (root) dfs(root, tmp);
        return res;
    }
};
