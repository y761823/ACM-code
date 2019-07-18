class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> stk;
        for (const string& str : tokens) {
            char c = str.front();
            if (isdigit(c) || (c == '-' && str.size() > 1)) {
                stk.push(stoi(str));
            } else {
                int p2 = stk.top(); stk.pop();
                int p1 = stk.top(); stk.pop();
                switch (c) {
                    case '+':
                        stk.push(p1 + p2);
                        break;
                    case '-':
                        stk.push(p1 - p2);
                        break;
                    case '*':
                        stk.push(p1 * p2);
                        break;
                    case '/':
                        stk.push(p1 / p2);
                        break;
                }
            }
        }
        return stk.top();
    }
};
