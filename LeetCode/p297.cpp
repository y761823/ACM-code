/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        stringstream sout;
        function<void(TreeNode* p)> dfs = [&](TreeNode* p) {
            if (p) {
                sout << p->val << ' ';
                dfs(p->left);
                dfs(p->right);
            } else {
                sout << "N ";
            }
        };
        dfs(root);
        return sout.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        stringstream sin(data);
        function<TreeNode*()> dfs = [&]() {
            TreeNode* p = nullptr;
            string s;
            if (sin >> s && s != "N") {
                p = new TreeNode(stoi(s));
                p->left = dfs();
                p->right = dfs();
            }
            return p;
        };
        return dfs();
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
