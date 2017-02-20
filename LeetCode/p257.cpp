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
    vector<string> res;
    
    void dfs(TreeNode* p, string &now) {
        if (!p) return ;
        
        if (!p->left && !p->right)
            return res.push_back(now + to_string(p->val));
            
        size_t oldSize = now.size();
        now += to_string(p->val); now += "->";
        dfs(p->left, now);
        dfs(p->right, now);
        now.resize(oldSize);
    }

    vector<string> binaryTreePaths(TreeNode* root) {
        if (!root) return {};
        string now;
        dfs(root, now);
        return res;
    }
};
