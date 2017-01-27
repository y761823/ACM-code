class Solution {
public:
    bool isValid(string s) {
        stack<char> stk;
        for (char c : s) {
            switch (c) {
                case '(':
                    stk.push(c);
                    break;
                case ')':
                    if (stk.empty() || stk.top() != '(')
                        return false;
                    stk.pop();
                    break;
                case '[':
                    stk.push(c);
                    break;
                case ']':
                    if (stk.empty() || stk.top() != '[')
                        return false;
                    stk.pop();
                    break;
                case '{':
                    stk.push(c);
                    break;
                case '}':
                    if (stk.empty() || stk.top() != '{')
                        return false;
                    stk.pop();
                    break;
            }
        }
        return stk.empty();
    }
};
