class Solution {
public:
    int longestValidParentheses(string s) {
        stack<int> stk;
        int res = 0, lastInvalid = -1;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '(') {
                stk.push(i);
            } else {
                if (!stk.empty() && s[stk.top()] == '(') {
                    stk.pop();
                    res = max(res, i - (!stk.empty() ? stk.top() : lastInvalid));
                } else {
                    while (!stk.empty()) stk.pop();
                    lastInvalid = i;
                }
            }
        }
        return res;
    }
};
