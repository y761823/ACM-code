class Solution {
public:
    vector<string> res;
    string now;
    
    void dfs(int lBracket, int rBracket) {
        if (lBracket == 0 && rBracket == 0)
            return res.push_back(now);
        if (lBracket) {
            now.push_back('(');
            dfs(lBracket - 1, rBracket + 1);
            now.pop_back();
        }
        if (rBracket) {
            now.push_back(')');
            dfs(lBracket, rBracket - 1);
            now.pop_back();
        }
    }

    vector<string> generateParenthesis(int n) {
        dfs(n, 0);
        return res;
    }
};
